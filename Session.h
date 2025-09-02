#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <set>
#include <map>
#include <mutex>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket,
            std::set<std::shared_ptr<Session>>& sessions,
            std::map<std::shared_ptr<Session>, std::string>& names,
            std::mutex& mutex)
            : socket_(std::move(socket)), sessions_(sessions), names_(names), mutex_(mutex) {}

    void start() {
        do_read_name();
    }

    void deliver(const std::string& msg) {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(msg),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (ec) {
                                         stop();
                                     }
                                 });
    }

    void stop() {
        std::lock_guard<std::mutex> lock(mutex_);
        sessions_.erase(shared_from_this());
        names_.erase(shared_from_this());
        socket_.close();
    }

private:
    void do_read_name() {
        auto self(shared_from_this());
        boost::asio::async_read_until(socket_, buffer_, '\n',
                                      [this, self](boost::system::error_code ec, std::size_t length) {
                                          if (!ec) {
                                              std::istream is(&buffer_);
                                              std::getline(is, name_);
                                              {
                                                  std::lock_guard<std::mutex> lock(mutex_);
                                                  sessions_.insert(self);
                                                  names_[self] = name_;
                                              }
                                              std::cout << "[Server] " << name_ << " connected.\n";
                                              do_read();
                                          } else {
                                              stop();
                                          }
                                      });
    }

    void do_read() {
        auto self(shared_from_this());
        boost::asio::async_read_until(socket_, buffer_, '\n',
                                      [this, self](boost::system::error_code ec, std::size_t length) {
                                          if (!ec) {
                                              std::istream is(&buffer_);
                                              std::string msg;
                                              std::getline(is, msg);

                                              std::string full_msg = name_ + ": " + msg + "\n";
                                              broadcast(full_msg);
                                              do_read();
                                          } else {
                                              stop();
                                          }
                                      });
    }

    void broadcast(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& session : sessions_) {
            if (session != shared_from_this()) {
                session->deliver(msg);
            }
        }
    }

    tcp::socket socket_;
    boost::asio::streambuf buffer_;
    std::string name_;
    std::set<std::shared_ptr<Session>>& sessions_;
    std::map<std::shared_ptr<Session>, std::string>& names_;
    std::mutex& mutex_;
};

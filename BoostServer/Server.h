#pragma once
#include "Session.h"

class Server {
public:
    Server(boost::asio::io_context& io_context, unsigned short port)
            : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket) {
                    if (!ec) {
                        auto session = std::make_shared<Session>(
                                std::move(socket), sessions_, names_, mutex_);
                        session->start();
                    }
                    do_accept();
                });
    }

    tcp::acceptor acceptor_;
    std::set<std::shared_ptr<Session>> sessions_;
    std::map<std::shared_ptr<Session>, std::string> names_;
    std::mutex mutex_;
};

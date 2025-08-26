//
// Created by nematpour on 8/26/2025.
//

#include "Session.h"

Session:: Session(tcp::socket socket) :socket_(std::move(socket)) {}

void Session::do_read()
{
        auto self = shared_from_this();
       boost::asio::async_read_until(socket_, buffer_, '\n',
            [this, self](boost::system::error_code ec,std::size_t length) {
                if (!ec) {
                    // Convert buffer_ to string
                    std::istream is(&buffer_);
                    std::string data;
                    std::getline(is, data); // reads up to '\n' (without it)

                    std::string response = "SERVER: " + data + "\n";
                    do_write(response);
                    do_read();
                } else {
                    socket_.close();
                }
            });



}

void Session::do_write(const std::string& message) {
    auto self = shared_from_this();
    // Copy message into a dynamic buffer since async_write may outlive this object
    write_msgs_ = message;
    boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_),
                             [this, self](boost::system::error_code ec,std::size_t/*length*/) {
                                 if (ec) {
                                     socket_.close();
                                 }
                                 // else, message sent; keep reading
                             });
}
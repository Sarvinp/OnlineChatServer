//
// Created by nematpour on 8/26/2025.
//

#ifndef BOOSTSERVER_SERVER_H
#define BOOSTSERVER_SERVER_H


#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, unsigned short port)
            : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    void do_accept();

    tcp::acceptor acceptor_;
};


#endif //BOOSTSERVER_SERVER_H

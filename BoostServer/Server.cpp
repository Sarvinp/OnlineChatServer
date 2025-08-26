//
// Created by nematpour on 8/26/2025.
//

#include "Server.h"
#include "Session.h"



void Server::do_accept() {


        acceptor_.async_accept(
                [this](boost::system::error_code ec,tcp::socket socket) {
                    if (!ec) {
                        std::make_shared<Session>(std::move(socket))->start();
                    }
                    // Accept another connection
                    do_accept();
                });

}
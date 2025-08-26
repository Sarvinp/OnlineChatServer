//
// Created by nematpour on 8/26/2025.
//

#ifndef BOOSTSERVER_SESSION_H
#define BOOSTSERVER_SESSION_H

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
    using boost::asio::ip::tcp;

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket socket);

        void start() {
            do_read();
        }

    private:
        void do_read();
        void do_write(const std::string& message) ;

        tcp::socket socket_;
        boost::asio::streambuf buffer_;
        std::string write_msgs_;
    };




#endif //BOOSTSERVER_SESSION_H

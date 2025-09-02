#include <iostream>
#include "Server.h"
int main(int argc, char* argv[]) {
    try {
        unsigned short port = 12345;
        if (argc > 1) {
            port = static_cast<unsigned short>(std::stoi(argv[1]));
        }

        boost::asio::io_context io_context;

        Server server(io_context, port);

        std::cout << "Server is listening on port " << port << std::endl;

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
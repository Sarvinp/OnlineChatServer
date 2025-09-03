#include "ChatServer.cpp"
#include <thread>

int main() {
    try {
        ChatServer server;

        std::thread server_thread([&server]() {
            server.run();
        });

        std::string input;
        std::cout << "Type '0' and press Enter to shut down the server.\n";
        while (std::getline(std::cin, input)) {
            if (input == "0") {
                std::cout << "[Server] Shutting down...\n";
                exit(0);  // Or implement a graceful shutdown flag
            }
        }

        server_thread.join();
    } catch (const std::exception& e) {
        std::cerr << "[Fatal] " << e.what() << "\n";
        return 1;
    }
    return 0;
}

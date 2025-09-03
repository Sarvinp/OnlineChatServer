#include <zmq.h>
#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include <algorithm>

class ChatServer {
public:
    ChatServer() {
        context = zmq_ctx_new();
        router = zmq_socket(context, ZMQ_ROUTER);
        if (!router) throw std::runtime_error("Failed to create ROUTER socket");

        if (zmq_bind(router, "tcp://*:5555") != 0)
            throw std::runtime_error("Failed to bind to tcp://*:5555");

        std::cout << "[ChatServer] Listening on tcp://*:5555\n";
    }

    ~ChatServer() {
        if (router) zmq_close(router);
        if (context) zmq_ctx_term(context);
    }

    void run() {
        while (true) {
            try {
                auto frames = receiveMultipart();
                if (frames.size() < 3) continue;

                std::string sender_id = frames[0];
                std::string message = frames[2];

                {
                    std::lock_guard<std::mutex> lock(clients_mutex);
                    if (std::find(clients.begin(), clients.end(), sender_id) == clients.end()) {
                        clients.push_back(sender_id);
                        std::cout << "[ChatServer] New client connected: " << sender_id << "\n";
                    }
                }

                std::string broadcast = "[Chat] " + sender_id + ": " + message;

                std::lock_guard<std::mutex> lock(clients_mutex);
                for (const auto& client_id : clients) {
                    if (client_id != sender_id) {
                        sendMultipart(client_id, broadcast);
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "[ChatServer] Error: " << e.what() << "\n";
            }
        }
    }

private:
    std::vector<std::string> receiveMultipart() {
        std::vector<std::string> frames;
        while (true) {
            zmq_msg_t msg;
            zmq_msg_init(&msg);
            zmq_recvmsg(router, &msg, 0);
            frames.emplace_back(static_cast<char*>(zmq_msg_data(&msg)), zmq_msg_size(&msg));
            zmq_msg_close(&msg);

            int more = 0;
            size_t more_size = sizeof(more);
            zmq_getsockopt(router, ZMQ_RCVMORE, &more, &more_size);
            if (!more) break;
        }
        return frames;
    }

    void sendMultipart(const std::string& client_id, const std::string& message) {
        zmq_send(router, client_id.data(), client_id.size(), ZMQ_SNDMORE);
        zmq_send(router, "", 0, ZMQ_SNDMORE);
        zmq_send(router, message.data(), message.size(), 0);
    }

    void* context;
    void* router;
    std::vector<std::string> clients;
    std::mutex clients_mutex;
};

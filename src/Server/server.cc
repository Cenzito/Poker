#include "server.h"
#include <Poco/Net/ServerSocket.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <thread>


std::vector<PokerServerConnection*> PokerServerConnection::connections;
std::mutex PokerServerConnection::connectionsMutex;


PokerServerConnection::PokerServerConnection(const StreamSocket& s) : TCPServerConnection(s) {
    std::lock_guard<std::mutex> guard(connectionsMutex);
    connections.push_back(this);
}


std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}


void PokerServerConnection::run() {
    StreamSocket& ss = socket();
    try {
        std::string accumulated;
        char buffer[256] = {0};
        int n = ss.receiveBytes(buffer, sizeof(buffer));
        while (n > 0) {
            accumulated.append(buffer, n);
            std::string message = trim(accumulated);

            if (accumulated.find("/quit") != std::string::npos) {
                ss.close(); // Close the socket
                break;
            }

            sendMessageToAll(message, ss);
            accumulated.clear();
            std::memset(buffer, 0, sizeof(buffer));
            n = ss.receiveBytes(buffer, sizeof(buffer));
        }
    } catch (Poco::Exception& exc) {
        std::cerr << "Connection error: " << exc.displayText() << std::endl;
    }

    std::lock_guard<std::mutex> guard(connectionsMutex);
    connections.erase(std::remove(connections.begin(), connections.end(), this), connections.end());
}


void PokerServerConnection::sendMessageToAll(const std::string& message, const StreamSocket& sender) {
    std::lock_guard<std::mutex> guard(connectionsMutex);

    // Use a thread for each send operation to perform them simultaneously
    std::vector<std::thread> sendThreads;
    sendThreads.reserve(connections.size());

    for (auto& connection : connections) {
        if (&connection->socket() != &sender) {
            // Create a thread to send the message
            sendThreads.emplace_back([connection, message]() {
                try {
                    connection->socket().sendBytes(message.data(), message.size());
                } catch (const Poco::Exception& exc) {
                    std::cerr << "Failed to send message: " << exc.displayText() << std::endl;
                    // Handle the error (e.g., logging, closing the socket, etc.)
                }
            });
        }
    }

    // Wait for all send operations to complete
    for (auto& thread : sendThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}


PokerServer::PokerServer(int port) {
    Poco::Net::ServerSocket svs(port);
    server = new Poco::Net::TCPServer(new Poco::Net::TCPServerConnectionFactoryImpl<PokerServerConnection>(), svs);
}


void PokerServer::start() {
    server->start();
}


void PokerServer::stop() {
    server->stop();
}

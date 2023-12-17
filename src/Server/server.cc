#include "server.h"
#include <Poco/Net/ServerSocket.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <thread>
#include "Creationaccount.hpp"

std::vector<PokerServerConnection*> PokerServerConnection::connections;
std::mutex PokerServerConnection::connectionsMutex;
std::map<StreamSocket*, ClientInfo> PokerServerConnection::clientCredentials; // Map to store client credentials

PokerServerConnection::PokerServerConnection(const StreamSocket& s) : TCPServerConnection(s) {
    std::lock_guard<std::mutex> guard(connectionsMutex);
    connections.push_back(this);
    clientCredentials[&socket()] = ClientInfo(); // Initialize with default ClientInfo
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}

void PokerServerConnection::run() {
    StreamSocket& ss = socket();
    std::string accumulated;
    char buffer[256] = {0};

    try {
        while (true) {
            int n = ss.receiveBytes(buffer, sizeof(buffer) - 1);
            if (n <= 0) break;

            accumulated.append(buffer, n);
            std::string message = trim(accumulated);

            if (!clientCredentials[&ss].isLoggedIn) {
                auto delimiterPos = message.find(':');
                if (delimiterPos != std::string::npos) {
                    clientCredentials[&ss].username = message.substr(0, delimiterPos);
                    clientCredentials[&ss].password = message.substr(delimiterPos + 1);
                    clientCredentials[&ss].isLoggedIn = true; // Set login status to true
                }
            } else {
                if (message.find("/quit") != std::string::npos) {
                    ss.close();
                    break;
                }
                sendMessageToAll(clientCredentials[&ss].username + ": " + message, ss);
            }

            accumulated.clear();
            std::memset(buffer, 0, sizeof(buffer));
        }
    } catch (Poco::Exception& exc) {
        std::cerr << "Connection error: " << exc.displayText() << std::endl;
    }

    std::lock_guard<std::mutex> guard(connectionsMutex);
    connections.erase(std::remove(connections.begin(), connections.end(), this), connections.end());
}

void PokerServerConnection::sendMessageToAll(const std::string& message, const StreamSocket& sender) {
    std::lock_guard<std::mutex> guard(connectionsMutex);
    for (auto& connection : connections) {
        if (&connection->socket() != &sender && clientCredentials[&connection->socket()].isLoggedIn) {
            std::thread([connection, message]() {
                try {
                    connection->socket().sendBytes(message.data(), message.size());
                } catch (const Poco::Exception& exc) {
                    std::cerr << "Failed to send message: " << exc.displayText() << std::endl;
                }
            }).join();
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

#include "server.h"
#include <Poco/Net/ServerSocket.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <thread>

#define BUFFER_SIZE 256

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, (last - first + 1));
}

std::vector<PokerServerConnection*> PokerServerConnection::connections;
std::mutex PokerServerConnection::connectionsMutex;
std::map<StreamSocket*, ClientInfo> PokerServerConnection::clientCredentials; 

PokerServerConnection::PokerServerConnection(const StreamSocket& s) : TCPServerConnection(s) {
    std::lock_guard<std::mutex> guard(connectionsMutex);
    connections.push_back(this);
    clientCredentials[&socket()] = ClientInfo(); 

    try {
        auto cards = dealer.dealCommunityCards(2);
        std::string cardMessage = createCardMessage(cards);
        socket().sendBytes(cardMessage.data(), cardMessage.length());
    } catch (const std::runtime_error& e) {
        std::cerr << "Error dealing cards: " << e.what() << std::endl;
    }
}


void PokerServerConnection::run() {
    StreamSocket& ss = socket();
    std::string accumulated;
    char buffer[BUFFER_SIZE] = {0};

    try {
        while (true) {
            int n = ss.receiveBytes(buffer, BUFFER_SIZE - 1);
            if (n <= 0) break; 
            if(processReceivedData(ss, buffer, n, accumulated)) break;
        }
    } catch (Poco::Exception& exc) {
        std::cerr << "Connection error: " << exc.displayText() << std::endl;
    }

    cleanupConnection();
}

bool PokerServerConnection::processReceivedData(StreamSocket& ss, char* buffer, int n, std::string& accumulated) {
    accumulated.append(buffer, n);
    std::string message = trim(accumulated)
    if (processCommands(ss, message)) {
        if(message.find("/bet") != std::string::npos){
            game.onRaise()
        }
        else if(message.find("/fold") != std::string::npos){
            game.onFold();
        }
        else if(message.find("/joinGame") != std::string::npos){
            size_t pos = message.find(":");
            std::string name = message.substr(pos + 1);
            PokerPlayer* player = new Pokerplayer(name);
            game.JoinGame(player);
        }
        else if(message.find(""))
        else{
            break;
        }
    }
    sendMessageToAll(clientCredentials[&ss].username + ": " + message, ss);
    

    accumulated.clear();
    std::memset(buffer, 0, sizeof(buffer));

    return false;
}

void PokerServerConnection::processLogin(StreamSocket& ss, std::string& message) {
    auto delimiterPos = message.find(':');
    if (delimiterPos != std::string::npos) {
        clientCredentials[&ss].username = message.substr(0, delimiterPos);
        clientCredentials[&ss].password = message.substr(delimiterPos + 1);
        clientCredentials[&ss].isLoggedIn = true;
    }
}

bool PokerServerConnection::processCommands(StreamSocket& ss, const std::string& message) {
    if (message.find("/quit") != std::string::npos) {
        ss.close();
        return true;
    }
    if (message.find("/bet") != std::string::npos){
        sendMessageTosender("/bet");
        return 
    }
    if (message.find("/fold") != std::string::npos){
        sendMessageTosender("/fold");
    }

    return false;
}

void PokerServerConnection::cleanupConnection() {
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

void PokerServerConnection::sendMessageTosender(const std::string& message, const StreamSocket& sender){
    std::lock_guard<std::mutex> guard(connectionsMutex);
    for (auto& connection : connections) {
        if (&connection->socket() == &sender) {
                try {
                    sender.sendBytes(message.data(), message.size());
                } catch (const Poco::Exception& exc) {
                    std::cerr << "Failed to send message: " << exc.displayText() << std::endl;
                }
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

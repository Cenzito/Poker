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
}


void PokerServerConnection::run() {
    StreamSocket& ss = socket();
    std::string accumulated;
    char buffer[BUFFER_SIZE] = {0};

    try {
        while (true) {
            int n = ss.receiveBytes(buffer, BUFFER_SIZE - 1);
            if (n <= 0 || processCommands(ss, buffer, n, accumulated)){
                break;
            }
            else{
                processReceivedData(ss, buffer, n, accumulated);
            }
            
        }
    } catch (Poco::Exception& exc) {
        std::cerr << "Connection error: " << exc.displayText() << std::endl;
    }

    cleanupConnection();
}

void PokerServerConnection::bet_command(StreamSocket& ss, char* buffer, int n, std::string& accumulated){
    size_t pos = message.find(":");
    std::string amount = message.substr(pos + 1);
    game.onRaise(amount.toInt());
}

void PokerServerConnection::fold_command(){
    size_t pos = message.find(":");
    std::string name = message.substr(pos + 1);
    game.fold(game.tableInfo.getPlayerInfo(name));
}

void PokerServerConnection::joingame_command(StreamSocket& ss, char* buffer, int n, std::string& accumulated){
    size_t pos = message.find(":");
    std::string name = message.substr(pos + 1);
    PokerPlayer* player = new Pokerplayer(name);
    game.JoinGame(player);
}

void PokerServerConnection::nextround_command(){
    game.nextBettingRound();
}

void PokerServerConnection::win_command(){
    size_t pos1 = message.find(":");
    std::string name = message.substr(pos1 + 1);
    size_t pos2 = message.substr(pos + 1).find(":")
    std::string amount = message.substr(pos2 + 1).toInt();
    game.distribute();
    game.win(game.tableInfo.getPlayerInfo(name));
}

void PokerServerConnection::Allin_command(){
    game.allin(game.tableInfo.getPlayerInfo(name));
}

void PokerServerConnection::resetGame_command(){
    game.nextHand();
}

void PokerServerConnection::setActivePlayer_command(){
    game.setNextCurrentPlayer();
}

void PokerServerConnection::setPlayerInfos_command(){
    game.setPlayerInfos();
}

void PokerServerConnection::processReceivedData(StreamSocket& ss, char* buffer, int n, std::string& accumulated) {
    accumulated.append(buffer, n);
    std::string message = trim(accumulated);

    if(message.find("/joinGame") != std::string::npos){
        joingame_command(ss, buffer, n, accumulated);
    }
    else if(message.find("/bet") != std::string::npos){
        bet_command(ss, buffer, n, accumulated);
    }
    else if(message.find("/fold") != std::string::npos){
        fold_command();
    }
    else if(message.find("/nextRound") != std::string::npos){
        nextround_command();
    }
    else if(message.find("/win") != std::string::npos){
        win_command();
    }
    else if(message.find("/Allin") != std::string::npos){
        Allin_command();
    }
    else if(message.find("/resetGame") != std::string::npos){
        resetGame_command();
    }
    else if(message.find("/setActivePlayer") != std::string::npos){
        setActivePlayer_command();
    }
    else if(message.find("/setPInf") != std::string::npos){

    }

    sendMessageToAll(clientCredentials[&ss].username + ": " + message, ss);
    

    accumulated.clear();
    std::memset(buffer, 0, sizeof(buffer));

    return false;
}

bool PokerServerConnection::processCommands(StreamSocket& ss, char* buffer, int n, std::string& accumulated) {
    accumulated.append(buffer, n);
    std::string message = trim(accumulated);

    if (message.find("/quit") != std::string::npos) {
        ss.close();
        return true;
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

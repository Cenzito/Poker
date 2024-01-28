#include "client.h"
#include <cstring>
#include <iostream>
#include <thread>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#define BUFFER_SIZE 256

PokerClient::PokerClient(const std::string& server_ip, int port){
    this->server_ip = server_ip;
    this->port = port;
    this->running = true;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        exit(1);
    }
}

PokerClient::~PokerClient() {
    CloseConnection();
}

void PokerClient::CloseConnection(){
    running = false;
    closesocket(sock);
    WSACleanup();
    if (recvThread.joinable()) {
        recvThread.join();
    }
}

void PokerClient::run() {
    setupConnection();
    messageLoop();
}

void PokerClient::setupConnection() {
    createSocket();
    connectToServer();
    startReceiverThread();
}

void PokerClient::createSocket() {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup();
        exit(1);
    }
}

void PokerClient::connectToServer() {
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address/ Address not supported. ");
    }
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        throw std::runtime_error("Failed to connect to server.");
    }
}

void PokerClient::startReceiverThread() {
    recvThread = std::thread(&PokerClient::receiveMessages, this);
}

void PokerClient::messageLoop() {
    while (running) {
        if (send_message.find("/quit") != std::string::npos) {
            running = false;
        }
        sendMessage(send_message);
    }
}

std::string PokerClient::get_message(std::string& message){
    return message;
}

void PokerClient::receiveMessages() {
    char buffer[BUFFER_SIZE] = {0};
    while (running) {
        int bytesReceived = recv(sock, buffer, 1024, 0);
        if (bytesReceived <= 0) {
            std::cerr << "Disconnected from server or error occurred.\n";
            this->running = false;
            break;
        }
        this->recv_message = std::string(buffer, bytesReceived);
    }
}

void PokerClient::sendMessage(const std::string& message) {
    if (send(sock, message.c_str(), message.size(), 0) == -1) {
        std::cerr << "Failed to send message. " << errno << std::endl;
        this->running = false;
    }
}


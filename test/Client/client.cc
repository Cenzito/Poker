#include "client.h"
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Creationaccount.hpp"

#define BUFFER_SIZE 1024

PokerClient::PokerClient(const std::string& server_ip, int port) 
    : serverIP(server_ip), serverPort(port), sockfd(-1), running(true), isCredentialsSent(false) {}

PokerClient::~PokerClient() {
    if (recvThread.joinable()) {
        recvThread.join();
    }
    if (sockfd != -1) {
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);
    }
}

void PokerClient::run() {
    connectToServer();
    sendCredentials();

    std::string message;
    while (running && std::getline(std::cin, message)) {
        sendMessage(message);
        if (message == "/quit") {
            running = false;
        }
    }
}

void PokerClient::connectToServer() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw std::runtime_error("Failed to create socket.");
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP.c_str(), &server_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address/ Address not supported.");
    }

    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        throw std::runtime_error("Failed to connect to server.");
    }

    recvThread = std::thread(&PokerClient::receiveMessages, this);
}

void PokerClient::receiveMessages() {
    char buffer[BUFFER_SIZE];
    while (running) {
        if (!isCredentialsSent) {
            continue;
        }

        std::memset(buffer, 0, BUFFER_SIZE);
        ssize_t len = read(sockfd, buffer, BUFFER_SIZE - 1);
        if (len <= 0) {
            std::cerr << "Disconnected from server or error occurred." << std::endl;
            running = false;
            break;
        }
        std::cout << buffer << std::endl;
    }
}

void PokerClient::sendCredentials() {
    const char* accountinformation = "Account.db";

    CreationAccount account = CreationAccount(accountinformation);

    const char* sql = "CREATE TABLE IF NOT EXISTS ACCOUNT("
                  "USERNAME TEXT PRIMARY KEY NOT NULL, "
                  "PASSWORD TEXT NOT NULL);";
    account.CreationTable(sql);

    std::string username, password, choice;
    std::cout<<"If you need to register, input register else login"<<std::endl;
    std::cin>>choice;
    if(choice == "register"){
        do{
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
        }while(account.Check_repetition(username));
    }
    else if(choice =="login"){
        do{
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
        }while(account.login(username, password)); 
    }
    //create the Pokerplayer based on the username by PokerPlayer()
    isCredentialsSent = true;
}

void PokerClient::sendMessage(const std::string& message) {
    if (send(sockfd, message.c_str(), message.size(), 0) == -1) {
        std::cerr << "Failed to send message." << std::endl;
        running = false;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <port>" << std::endl;
        return 1;
    }

    try {
        std::string serverIP = argv[1];
        int port = std::stoi(argv[2]);
        PokerClient client(serverIP, port);
        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Disconnected from server." << std::endl;
    return 0;
}

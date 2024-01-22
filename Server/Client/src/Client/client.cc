#include "client.h"
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 256

PokerClient::PokerClient(const std::string& server_ip, int port) : 
    serverIP(server_ip), 
    serverPort(port), 
    sockfd(-1), 
    running(true), 
    isCredentialsSent(true), 
    player("", 500),
    roundStarted(false) {}

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
    setupConnection();
    messageLoop();
}

void PokerClient::setupConnection() {
    createSocket();
    connectToServer();
    startReceiverThread();
}

void PokerClient::createSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw std::runtime_error("Failed to create socket.");
    }
}

void PokerClient::connectToServer() {
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP.c_str(), &server_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address/ Address not supported. ");
    }
    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        throw std::runtime_error("Failed to connect to server.");
    }
}

void PokerClient::startReceiverThread() {
    recvThread = std::thread(&PokerClient::receiveMessages, this);
}

void PokerClient::messageLoop() {
    std::string message;
    while (running && std::getline(std::cin, message)) {
        processUserInput(message);
        if (message.find("/quit") != std::string::npos) {
            running = false;
        }
    }
}

void PokerClient::processUserInput(const std::string& message) {
    if (message.find("/bet ") == 0 && !player.folded()) {
        handleBet(message);
    } else if (message == "/fold" && !player.folded()) {
        handleFold();
    } else if (message.find("/raise ") == 0 && !player.folded()) {
        handleRaise(message);
    } 
    else {
        sendMessage(message);
    }
}

void PokerClient::handleBet(const std::string& message) {
    executePlayerAction(message, "bet");
}

void PokerClient::handleRaise(const std::string& message) {
    executePlayerAction(message, "raise");
}

void PokerClient::handleFold() {
    player.fold();
    sendMessage("fold");
}

void PokerClient::executePlayerAction(const std::string& message, const std::string& action) {
    // The structure of the message is "/command bet-value"
    size_t pos = message.find(" ") + 1;
    int amount = std::stoi(message.substr(pos));
    try {
        player.bet(amount);
        sendMessage(action + ":" + std::to_string(amount));
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

void PokerClient::receiveMessages() {
    char buffer[BUFFER_SIZE] = {0};
    while (running) {
        if (!isCredentialsSent) {
            continue;
        }
        ssize_t len = read(sockfd, buffer, BUFFER_SIZE - 1);
        if (len <= 0) {
            std::cerr << "Disconnected from server or error occurred.\n";
            running = false;
            break;
        }
        std::cout << buffer << std::endl;
    }
}

void PokerClient::sendMessage(const std::string& message) {
    if (send(sockfd, message.c_str(), message.size(), 0) == -1) {
        std::cerr << "Failed to send message. " << errno << std::endl;
        running = false;
    }
}


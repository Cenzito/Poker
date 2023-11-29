#include "server.h"
#include "Poco/Net/SocketNotification.h"
#include <fstream>
#include <iostream>
#include <string>

PokerServer::PokerServer(const std::string& port) 
    : serverSocket(std::stoi(port)), thread("PokerServerThread") {
    reactor.addEventHandler(serverSocket, Poco::NObserver<PokerServer, Poco::Net::ReadableNotification>(*this, &PokerServer::onSocketReadable));
}

PokerServer::~PokerServer() {
    reactor.stop();
    thread.join();
}

void PokerServer::run() {
    thread.start(reactor);
    std::cout << "Server is running..." << std::endl;
    Poco::Thread::sleep(Poco::Timespan::SECONDS * 60 * 60); // Keep server running for an hour
}

void PokerServer::onSocketReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf) {
    Poco::Net::StreamSocket ss = serverSocket.acceptConnection();
    char buffer[1024];
    int n = ss.receiveBytes(buffer, sizeof(buffer));
    std::string message(buffer, n);
    std::cout << "Received: " << message << std::endl;

    ss.sendBytes(message.data(), message.size());
}


void PokerServer::onSocketShutdown(const Poco::AutoPtr<Poco::Net::ShutdownNotification>& pNf) {
    std::cout << "Socket is shutting down." << std::endl;
}

int mainServer(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: PokerServer <port>" << std::endl;
        return 1;
    }
    PokerServer server(argv[1]);
    server.run();

    return 0;
}

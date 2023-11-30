#include "server.h"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <iostream>
#include <string>


PokerServerConnection::PokerServerConnection(const Poco::Net::StreamSocket& socket)
: TCPServerConnection(socket) {
}


void PokerServerConnection::run() {
    Poco::Net::StreamSocket& ss = socket();
    try {
        char buffer[1024] = {0};
        int n = ss.receiveBytes(buffer, sizeof(buffer));
        while (n > 0) {
            std::string message(buffer, n); // Construct a string from buffer
            std::cout << "Received: " << message << std::endl;
            // Echo back the message
            ss.sendBytes(buffer, n);
            // Read next message
            n = ss.receiveBytes(buffer, sizeof(buffer));
        }
    } catch (Poco::Exception& exc) {
        std::cerr << "Connection error: " << exc.displayText() << std::endl;
    }
}


PokerServer::PokerServer(int port) {
    Poco::Net::ServerSocket svs(port);
    _server = new Poco::Net::TCPServer(new Poco::Net::TCPServerConnectionFactoryImpl<PokerServerConnection>(), svs);
}


void PokerServer::start() {
    _server->start();
}


void PokerServer::stop() {
    _server->stop();
}

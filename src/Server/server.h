#ifndef SERVER_H
#define SERVER_H

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <Poco/Net/TCPServerConnection.h>
#include <vector>
#include <mutex>

using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;

class PokerServerConnection : public TCPServerConnection {
public:
    PokerServerConnection(const StreamSocket& s);
    void run() override;

    static void sendMessageToAll(const std::string& message, const StreamSocket& sender);

private:
    static std::vector<PokerServerConnection*> connections;
    static std::mutex connectionsMutex;
};

class PokerServer {
public:
    PokerServer(int port);
    void start();
    void stop();

private:
    Poco::Net::TCPServer* server;
};

#endif // SERVER_H

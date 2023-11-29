#ifndef SERVER_H
#define SERVER_H

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/NObserver.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include <string>

class PokerServer {
    Poco::Net::ServerSocket serverSocket;
    Poco::Net::SocketReactor reactor;
    Poco::Thread thread;

public:
    PokerServer(const std::string& port);
    ~PokerServer();
    void run();
    void onSocketReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>& pNf);
    void onSocketShutdown(const Poco::AutoPtr<Poco::Net::ShutdownNotification>& pNf);
};

#endif // SERVER_H

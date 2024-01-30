#ifndef SERVER_H
#define SERVER_H

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <Poco/Net/TCPServerConnection.h>
#include <vector>
#include <mutex>
#include <map>
#include <string>
#include "dealer.h"

using Poco::Net::TCPServerConnection;
using Poco::Net::StreamSocket;

/**
 * @brief Structure to store client information.
 * 
 * @param username The username of the client.
 * @param password The password of the client.
 * @param isLoggedIn Flag indicating if the client is logged in.
 */
struct ClientInfo {
    std::string username;
    std::string password;
    bool isLoggedIn;

    ClientInfo() : isLoggedIn(false) {}
};

/**
 * @brief Represents a connection to a poker server.
 * 
 * This class manages the individual connection to a poker client, handling message 
 * reception and dispatch.
 */
class PokerServerConnection : public TCPServerConnection {
public:
    /**
     * @brief Construct a new Poker Server Connection object
     * 
     * @param s 
     */
    PokerServerConnection(const StreamSocket& s);

    void run() override;

    void bet_command(StreamSocket& ss, char* buffer, int n, std::string& accumulated);

    void fold_command();

    void joingame_command(StreamSocket& ss, char* buffer, int n, std::string& accumulated);

    void nextround_command();

    void win_command();

    void Allin_command();

    void resetGame_command();

    void setActivePlayer_command();

    void setPlayerInfos_command(); 

    static void sendMessageToAll(const std::string& message, const StreamSocket& sender);

    static void sendMessageTosender(const std::string& message, const StreamSocket& sender);

private:
    static std::vector<PokerServerConnection*> connections; ///< Static list of active connections.
    static std::mutex connectionsMutex; ///< Mutex for managing access to the connections list.
    static std::map<StreamSocket*, ClientInfo> clientCredentials; ///< Map to store client credentials
    GameLocal game = GameLocal(5);
    std::vector

    /**
     * @brief Processes received data from the client.
     * 
     * @param ss The client's socket.
     * @param buffer The data buffer.
     * @param n The number of bytes received.
     * @param accumulated The accumulated message string.
     */
    void processReceivedData(StreamSocket& ss, char* buffer, int n, std::string& accumulated);

    /**
     * @brief Processes login information from the client.
     * 
     * @param ss The client's socket.
     * @param message The received login message.
     */
    void processLogin(StreamSocket& ss, std::string& message);

    /**
     * @brief Processes commands from the client.
     * 
     * @param ss The client's socket.
     * @param message The received command message.
     * @return True if a command was processed and actioned, otherwise false.
     */
    bool processCommands(StreamSocket& ss, const std::string& message);

    /**
     * @brief Cleans up the connection when it is closed.
     * 
     * Removes the connection from the active connections list and performs necessary cleanup.
     */
    void cleanupConnection();
};

/**
 * @brief Poker server class.
 * 
 * This class encapsulates a poker server that manages connections and client interactions.
 */
class PokerServer {
public:
    PokerServer(int port);

    void start();

    void stop();

private:
    Poco::Net::TCPServer* server; ///< Pointer to the internal Poco TCPServer instance.
};

#endif // SERVER_H

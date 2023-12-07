#ifndef SERVER_H
#define SERVER_H

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <Poco/Net/TCPServerConnection.h>
#include <vector>
#include <mutex>
#include <map>
#include <string>

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
     * @brief Constructor for PokerServerConnection.
     * 
     * @param s The stream socket associated with the connection.
     */
    PokerServerConnection(const StreamSocket& s);

    /**
     * @brief Main function to run the connection.
     * 
     * Handles receiving and processing client messages.
     */
    void run() override;

    /**
     * @brief Sends a message to all connected clients except the sender.
     * 
     * @param message The message to be sent.
     * @param sender The sender's socket, to exclude from receiving the message.
     */
    static void sendMessageToAll(const std::string& message, const StreamSocket& sender);

private:
    static std::vector<PokerServerConnection*> connections; ///< Static list of active connections.
    static std::mutex connectionsMutex; ///< Mutex for managing access to the connections list.
    static std::map<StreamSocket*, ClientInfo> clientCredentials; // Map to store client credentials
};

/**
 * @brief Poker server class.
 * 
 * This class encapsulates a poker server that manages connections and client interactions.
 */
class PokerServer {
public:
    /**
     * @brief Constructor for PokerServer.
     * 
     * Initializes a poker server on the specified port.
     * 
     * @param port The port on which the server will listen for connections.
     */
    PokerServer(int port);

    /**
     * @brief Starts the poker server.
     * 
     * Launches the server, allowing it to accept connections.
     */
    void start();

    /**
     * @brief Stops the poker server.
     * 
     * Shuts down the server and frees up resources.
     */
    void stop();

private:
    Poco::Net::TCPServer* server; ///< Pointer to the internal Poco TCPServer instance.
};

#endif // SERVER_H

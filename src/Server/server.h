/**
 * @file server.h
 * @brief This file contains the function declarations and class definitions for the Poker server.
 *
 * This file describes the functionality of the Poker server. It includes the definition
 * of the PokerServer and PokerServerConnection classes, which manage the server operations
 * and client connections, respectively.
 */

#ifndef POKER_SERVER_H
#define POKER_SERVER_H

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <Poco/Net/TCPServerConnection.h>

/**
 * @class PokerServerConnection
 * @brief Manages a single client connection in the Poker server.
 *
 * Inherits from Poco::Net::TCPServerConnection. This class is responsible for handling 
 * the communication between the server and a connected client, including receiving 
 * messages and sending responses.
 */
class PokerServerConnection : public Poco::Net::TCPServerConnection {
public:
    /**
     * @brief Constructor for PokerServerConnection.
     * @param socket The StreamSocket associated with the client connection.
     */
    PokerServerConnection(const Poco::Net::StreamSocket& socket);

    /**
     * @brief Handles the client-server communication.
     * 
     * Overrides the run method from TCPServerConnection. This method contains the logic 
     * for handling incoming messages from the client and sending responses back.
     */
    void run() override;
};

/**
 * @class PokerServer
 * @brief Manages the Poker game server.
 *
 * This class is responsible for initializing and managing the server, including 
 * starting and stopping the server and handling incoming client connections.
 */
class PokerServer {
public:
    /**
     * @brief Constructor for PokerServer.
     * @param port The port number on which the server will listen for incoming connections.
     */
    PokerServer(int port);

    /**
     * @brief Starts the server.
     * 
     * Initializes and starts the TCP server, allowing it to accept incoming client connections.
     */
    void start();

    /**
     * @brief Stops the server.
     * 
     * Stops the TCP server, ceasing to accept incoming client connections.
     */
    void stop();

private:
    Poco::Net::TCPServer* _server; ///< Pointer to the internal TCPServer instance.
};

#endif // POKER_SERVER_H

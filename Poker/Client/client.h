#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include "GameLogic/PokerPlayer.hpp"
#include <thread>
#include <string>
#include <winsock2.h>

class PokerClient {
public:
    /**
     * @brief Constructs a new PokerClient.
     * @param server_ip The IP address of the poker server.
     * @param port The port number of the poker server.
     */
    PokerClient(const std::string& server_ip, int port);

    /**
     * @brief Destroys the PokerClient.
     */
    ~PokerClient();

    /**
     * @brief Runs the client application.
     */
    void run();

    /**
     * @brief Sets up the connection to the server.
     */
    void setupConnection();

    /**
     * @brief Creates a socket for communication with the server.
     */
    void createSocket();

    /**
     * @brief Connects to the server using the specified IP and port.
     */
    void connectToServer();

    /**
     * @brief Starts a thread for receiving messages from the server.
     */
    void startReceiverThread();

    /**
     * @brief Enters the main loop for processing user input and server messages.
     */
    void messageLoop();

    /**
     * @brief Sends a message to the server.
     * @param message The message to be sent.
     */
    void sendMessage(const std::string& message);

    /**
     * @brief Continuously receives and processes messages from the server.
     */
    void receiveMessages();

    /*
     * This function closes the connection
     */
    void CloseConnection();

    /*
     *This function can get message from the action that player does
     */
    std::string get_message(std::string& message);

    // Attributes
    std::atomic<bool> running; ///< Flag to control the running state of the client.
    std::atomic<bool> isCredentialsSent; ///< Flag to indicate whether credentials have been sent.
    std::thread recvThread; ///< Thread for handling incoming messages.
    PokerPlayer player = PokerPlayer(""); ///< PokerPlayer attributes for the client.
    SOCKET sock;
    std::string server_ip;
    int port;
    std::string recv_message;
    std::string send_message;
};

#endif // CLIENT_H

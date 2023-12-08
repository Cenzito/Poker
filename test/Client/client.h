#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <atomic>
#include <thread>

/**
 * @brief Handles the client-side communication with a poker server.
 * 
 * This class encapsulates the functionality necessary for a client to connect to,
 * communicate with, and interact with a poker server. It manages the connection,
 * sends and receives messages, and handles the user's credentials.
 */
class PokerClient {
public:
    /**
     * @brief Constructs a new PokerClient.
     * 
     * Initializes a client with the server IP and port.
     * 
     * @param server_ip The IP address of the poker server.
     * @param port The port number of the poker server.
     */
    PokerClient(const std::string& server_ip, int port);

    /**
     * @brief Destroys the PokerClient.
     * 
     * Cleans up resources, ensures the socket is closed, and joins the receiving thread.
     */
    ~PokerClient();

    /**
     * @brief Runs the client application.
     * 
     * Connects to the server, sends credentials, and enters the main message handling loop.
     */
    void run();

private:
    /**
     * @brief Establishes connection to the poker server.
     * 
     * Sets up the socket and connects to the server based on the provided IP and port.
     */
    void connectToServer();

    /**
     * @brief Continuously receives messages from the server.
     * 
     * Listens for messages from the server and prints them out. Runs on a separate thread.
     */
    void receiveMessages();

    /**
     * @brief Sends user credentials to the server.
     * 
     * Prompts the user for username and password and sends these credentials to the server.
     */
    void sendCredentials();

    /**
     * @brief Sends a message to the server.
     * 
     * @param message The message string to be sent.
     */
    void sendMessage(const std::string& message);

    std::string serverIP; ///< The IP address of the server.
    int serverPort; ///< The port number of the server.
    int sockfd; ///< Socket file descriptor for communication with the server.
    std::atomic<bool> running; ///< Flag to control the running state of the client.
    std::atomic<bool> isCredentialsSent; ///< Flag to indicate whether credentials have been sent.
    std::thread recvThread; ///< Thread for handling incoming messages.
};

#endif // CLIENT_H

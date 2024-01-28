#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include "GameLogic/PokerPlayer.hpp"

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
     * @brief Sends a message to the server.
     * @param message The message to be sent.
     */
    void sendMessage(const std::string& message);


private:
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
     * @brief Authenticates the user by sending credentials to the server.
     */
    void authenticateUser();

    /**
     * @brief Enters the main loop for processing user input and server messages.
     */
    void messageLoop();

    /**
     * @brief Processes user input and performs corresponding actions.
     * @param message The input message from the user.
     */
    void processUserInput(const std::string& message);

    /**
     * @brief Handles the 'bet' action of the user.
     * @param message The bet command message.
     */
    void handleBet(const std::string& message);

    /**
     * @brief Handles the 'raise' action of the user.
     * @param message The raise command message.
     */
    void handleRaise(const std::string& message);

    /**
     * @brief Handles the 'fold' action of the user.
     */
    void handleFold();

    /**
     * @brief Executes a player action (bet or raise) and sends the action to the server.
     * @param message The command message containing the action.
     * @param action The action type (bet or raise).
     */
    void executePlayerAction(const std::string& message, const std::string& action);

    /**
     * @brief Continuously receives and processes messages from the server.
     */
    void receiveMessages();


    // Attributes
    std::string serverIP; ///< The IP address of the server.
    uint16_t serverPort; ///< The port number of the server.
    int sockfd; ///< Socket file descriptor for communication with the server.
    std::atomic<bool> running; ///< Flag to control the running state of the client.
    std::atomic<bool> isCredentialsSent; ///< Flag to indicate whether credentials have been sent.
    std::thread recvThread; ///< Thread for handling incoming messages.
    PokerPlayer player; ///< PokerPlayer attributes for the client.
    bool roundStarted; ///< Indicator if a round has started
};

#endif // CLIENT_H

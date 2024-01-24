 # Poker Client

This is a simple poker client written in C++ that allows users to connect to a poker server, authenticate, and play poker.

## Getting Started

### Prerequisites

To run this code, you will need the following:

* A C++ compiler
* A Linux operating system

### Building the Code

To build the code, simply run the following command in the project directory:

```
make
```

This will create an executable file named `PokerClient`.

### Running the Code

To run the code, simply run the following command in the project directory:

```
./PokerClient <server_ip> <port>
```

Where:

* `<server_ip>` is the IP address of the poker server
* `<port>` is the port number of the poker server

## Code Overview

The code is organized into the following files:

* `client.h`: This file contains the declaration of the `PokerClient` class.
* `client.cpp`: This file contains the implementation of the `PokerClient` class.

### The `PokerClient` Class

The `PokerClient` class is the main class in the code. It represents a poker client that can connect to a poker server, authenticate, and play poker.

The `PokerClient` class has the following member variables:

* `serverIP`: The IP address of the poker server.
* `serverPort`: The port number of the poker server.
* `sockfd`: The socket file descriptor.
* `running`: A boolean value that indicates whether the client is running.
* `isCredentialsSent`: A boolean value that indicates whether the client has sent its credentials to the server.
* `player`: A `Player` object that represents the player.
* `roundStarted`: A boolean value that indicates whether the round has started.

The `PokerClient` class has the following member functions:

* `run()`: This function starts the client.
* `setupConnection()`: This function creates a socket, connects to the server, and starts a receiver thread.
* `authenticateUser()`: This function authenticates the user with the server.
* `messageLoop()`: This function handles user input and sends messages to the server.
* `processUserInput()`: This function processes user input.
* `handleBet()`: This function handles a bet action from the user.
* `handleRaise()`: This function handles a

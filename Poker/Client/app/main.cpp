#include <iostream>
#include "client.h"

int main(int argc, char *argv[]) {
    
    try { 
        int port = 5000; // Set your desired port here
        std::string serverIP = "127.0.0.1";
        PokerClient client(serverIP, port);
        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Disconnected from server." << std::endl;
    return 0;
}

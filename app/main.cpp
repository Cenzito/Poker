#include <iostream>
#include "server.h"

int main() {
    int port = 5000; // Set your desired port here
    PokerServer server(port);
    server.start();

    std::cout << "Server is running on port " << port << ". Press enter to exit." << std::endl;
    std::cin.get();

    server.stop();
    return 0;
}

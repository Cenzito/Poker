#include <iostream>
#include "server.h"
#include "poker_table_state.h"

int main(int argc, char** argv) {
    int port = 5000; // Set your desired port here

    if (argc > 1) {
        port = std::stoi(argv[1]);
    }

    PokerServer server(port);
    server.start();

    std::cout << "Server is running on port " << port << ". Press enter to exit." << std::endl;
    std::cin.get();

    server.stop();
    return 0;
}

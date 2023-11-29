#include "server.h"
#include <iostream>

int main() {
    try {
        PokerServer server("9998"); // Server starts on port 9999
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

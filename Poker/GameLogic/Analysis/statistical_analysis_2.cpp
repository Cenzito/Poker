#include "statistical_analysis_2.h"
#include <sstream>

int main() {
    std::ifstream file("poker_game_1.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    PokerWinRate pokerWinRate;
    std::string handData;

    while (getline(file, handData)) {

        pokerWinRate.processHand(handData);
    }

    file.close();

    // Example: Display the win rate for a specific player
    std::string playerName = "playerName"; // Replace with an actual player name
    std::cout << "Win rate for " << playerName << ": "
              << pokerWinRate.getWinRate(playerName) * 100 << "%" << std::endl;

    return 0;
}


void PokerWinRate::processHand(const std::string& handData) {
    std::istringstream iss(handData);
    std::string line;
    while (std::getline(iss, line)) {
        // Parse the line to find player names and whether they won or lost
        // This is a simplified example; you'll need to modify it to parse your specific data format
        if (line.find("collected") != std::string::npos) {
            std::string playerName = /* extract player name from line */;
            processPlayerResult(playerName, true);
        }
    }
}

void PokerWinRate::processPlayerResult(const std::string& playerName, bool won) {
    PlayerStats& stats = playerStats[playerName];
    stats.games++;
    if (won) {
        stats.wins++;
    }
}

double PokerWinRate::getWinRate(const std::string& playerName) const {
    auto it = playerStats.find(playerName);
    if (it != playerStats.end()) {
        const PlayerStats& stats = it->second;
        if (stats.games == 0) return 0.0;
        return static_cast<double>(stats.wins) / stats.games;
    }
    return 0.0;
}







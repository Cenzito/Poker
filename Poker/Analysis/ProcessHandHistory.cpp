#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "AnalysisDiego.hpp"
#include <QApplication>



std::vector<Hand> parseHandHistory(const std::string& fileName) {
    std::vector<Hand> handHistory;
    std::ifstream inputFile(fileName);


    if (!inputFile.is_open()) {
        qDebug() << "Error: Unable to open file " << QString::fromStdString(fileName);
        return handHistory;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.find("*** HOLE CARDS ***") != std::string::npos) {
            // Process hands starting from "*** HOLE CARDS ***"
            std::getline(inputFile, line); // Skip next line

            while (std::getline(inputFile, line)) {
                if (line.find("*** SUMMARY ***") != std::string::npos) {
                    break; // Stop when reaching "*** SUMMARY ***"
                }

                // Extract player, street, and action from the line
                std::istringstream iss(line);
                std::string playerName, street, actionStr;
                iss >> playerName;

                if (playerName.back() == ':') {
                    playerName.pop_back(); // Remove trailing ':'
                }

                iss >> street >> actionStr;

                Action2 action;
                if (actionStr == "calls") {
                    action = Call;
                } else if (actionStr == "raises") {
                    action = Raise;
                } else if (actionStr == "bets") {
                    action = Bet;
                } else if (actionStr == "folds") {
                    action = Fold;
                } else {
                    // Handle other actions as needed
                    continue;
                }

                Hand hand1 = Hand(playerName, street, action);

                handHistory.emplace_back(playerName, street, action);
            }
        }
    }

    inputFile.close();
    return handHistory;
}

int displayParsed() {
    // Replace "" with the actual file name
    std::string fileName = "../Poker/Analysis/PokerHands1.txt";

    std::vector<Hand> handHistory = parseHandHistory(fileName);


    qDebug() << 1;
    // Display the parsed hand history
    qDebug() << handHistory.size();
    for (const auto& hand : handHistory) {
        qDebug() << "ppp";
        qDebug() << "Player: " << QString::fromStdString(hand.player) << ", Street: " << QString::fromStdString(hand.street) << ", Action: " << hand.action;
    }

    return 0;
}

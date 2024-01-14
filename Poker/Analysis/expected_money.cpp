// expected_money.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "expected_money.hpp"
#include <regex>

Hand::Hand(std::string& player, std::string& street, std::string& action, double chips)
    : player(player), street(street), action(action), chips(chips) {}

Hand::Hand() {}

std::vector<Hand> ReadPlayerHands(std::string file_name, std::string player_name) {
    std::ifstream file(file_name);
    std::string line;
    std::vector<Hand> player_hands;
    std::string street;
    std::string action;
    double chips = 0.0;

    while (std::getline(file, line)) {
        if (line.empty()) {
            street = "";
            action = "";
            chips = 0.0;
            continue;
        } else {

            if (line.find("Seat") != std::string::npos && line.find(player_name) != std::string::npos){
                // Extract chip count from the line
                std::regex chipRegex("Seat \\d+: " + player_name + " \\((\\d+) in chips\\)");
                std::smatch chipMatch;
                if (std::regex_search(line, chipMatch, chipRegex)) {
                    chips = std::stod(chipMatch[1]);
                    std::cout << "Chips: " << chips << std::endl;
                    // You can store 'chips' in a variable if needed
                }

            }

            if (line.find("*** HOLE CARDS ***") != std::string::npos) {
                street = "Preflop";
            }
            if (line.find("*** FLOP ***") != std::string::npos) {
                street = "Flop";
            }
            if (line.find("*** TURN ***") != std::string::npos) {
                street = "Turn";
            }
            if (line.find("*** RIVER ***") != std::string::npos) {
                street = "River";
            }

            if (line.find(player_name) != std::string::npos) {
                if (line.find("folds") != std::string::npos) {
                    action = "Fold";
                }
                if (line.find("calls") != std::string::npos) {
                    action = "Call";
                }
                if (line.find("bets") != std::string::npos) {
                    action = "Bet";
                }
                if (line.find("raises") != std::string::npos) {
                    action = "Raise";
                }
    
            } else {
                action = "";
            }

            if (street != "" && action != "") {
                Hand hand = {player_name, street, action, chips};
                player_hands.push_back(hand);
            }
        }
    }
    return player_hands;
}

int main() {
    // Sample data (replace this with your actual hand history data)
    std::vector<Hand> hand_history = ReadPlayerHands("PokerHands3.txt", "remi418");
    // Print the hand history
    for (auto hand : hand_history) {
        std::cout << hand.player << " " << hand.street << " " << hand.action << std::endl;
    }
    return 0;
}
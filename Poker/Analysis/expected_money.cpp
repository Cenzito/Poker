// expected_money.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "expected_money.hpp"

Hand::Hand(std::string& player, std::string& street, std::string& action, double money_won)
    : player(player), street(street), action(action), money_won(money_won) {}

Hand::Hand() {}

std::vector<Hand> ReadPlayerHands(std::string file_name, std::string player_name) {
    std::ifstream file(file_name);
    std::string line;
    std::vector<Hand> player_hands;
    std::string street;
    std::string action;
    double money_won = 0.0;

    while (std::getline(file, line)) {
        if (line.empty()) {
            street = "";
            action = "";
            continue;
        } else {
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
                if (line.find("wins") != std::string::npos) {
                    size_t pos = line.find("$");
                    if (pos != std::string::npos) {
                        std::istringstream money_stream(line.substr(pos + 1));
                        money_stream >> money_won;
                    }
                }
            } else {
                action = "";
            }

            if (street != "" && action != "") {
                Hand hand = {player_name, street, action, money_won};
                player_hands.push_back(hand);
            }
        }
    }
    return player_hands;
}

int main() {
    std::vector<Hand> hand_history = ReadPlayerHands("PokerHands1.txt", "remi418");

    double total_money_won = 0.0;
    int hands_played = 0;

    for (const auto& hand : hand_history) {
        if (hand.player == "remi418") {
            total_money_won += hand.money_won;
            hands_played++;
        }
    }

    if (hands_played > 0) {
        double average_money_won = total_money_won / hands_played;
        std::cout << "Average money won by remi418: $" << average_money_won << std::endl;
    } else {
        std::cout << "No hands played by remi418." << std::endl;
    }

    return 0;
}
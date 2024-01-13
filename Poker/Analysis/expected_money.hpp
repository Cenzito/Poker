// expected_money.hpp

#ifndef EXPECTED_MONEY_HPP
#define EXPECTED_MONEY_HPP

#include <string>
#include <vector>

class Hand {
public:
    std::string player;  // Player name
    std::string street;  // Street (e.g., 'preflop', 'flop', 'turn', 'river')
    std::string action;  // Action taken by the player (e.g., 'Bet', 'Raise', 'Call', 'Fold')
    double money_won;    // Amount of money won in this hand

    Hand(std::string& player, std::string& street, std::string& action, double money_won);
    Hand();
};

std::vector<Hand> ReadPlayerHands(std::string file_name, std::string player_name);

#endif // EXPECTED_MONEY_HPP

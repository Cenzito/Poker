// margins.hpp

// margins.hpp

#ifndef MARGINS_HPP
#define MARGINS_HPP

#include <string>
#include <vector>

class Hand {
public:
    std::string player;  // Player name
    std::string street;  // Street (e.g., 'preflop', 'flop', 'turn', 'river')
    std::string action;  // Action taken by the player (e.g., 'Bet', 'Raise', 'Call', 'Fold')
    double chips;    // Amount of money won in this hand
    double chips_start;

    Hand(std::string& player, std::string& street, std::string& action, double chips, double chips_start);
    Hand();
};

std::vector<double> ReadMargins(std::string file_name, std::string player_name);

#endif // EXPECTED_MONEY_HPP

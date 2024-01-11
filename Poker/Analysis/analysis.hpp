#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP
#include <string>
#include <vector>

class Hand {
public:
    std::string player;  // Player name
    std::string street;  // Street (e.g., 'preflop', 'flop', 'turn', 'river')
    std::string action;       // Action taken by the player (e.g., 'Bet', 'Raise', 'Call', 'Fold')
    Hand(std::string& player, std::string& street, std::string& action);
    Hand();
};


std::vector<Hand> ReadPlayerHands(std::string file_name, std::string player_name);
int Display_Hand_size();

#endif // ANALYSIS_HPP

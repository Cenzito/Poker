#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP
#include <string>
#include <vector>

class Hand {
public:
    std::string player;  // Player name
    std::string street;  // Street (e.g., 'preflop', 'flop', 'turn', 'river')
    std::string action;      // Action taken by the player (e.g., 'Bet', 'Raise', 'Call', 'Fold')
    double chips;    // Amount of money won in this hand
    double chips_start;
    Hand(std::string& player, std::string& street, std::string& action, double chips, double chips_start);
    Hand();
};


std::vector<Hand> ReadPlayerHands(std::string file_name, std::string player_name);
std::vector<double> ReadMargins(std::string file_name, std::string player_name);
double calculate_af(const std::vector<Hand>& hand_history, const std::string& player_name);
double calculate_vpip_percentage(const std::vector<Hand>& hand_history, const std::string& player_name);
double average_margin(const std::vector<Hand>& hand_history, const std::string& player_name);


#endif // ANALYSIS_HPP


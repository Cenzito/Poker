#ifndef ANALYSISDIEGO_HPP
#define ANALYSISDIEGO_HPP

#include <string>
#include <vector>

enum Action { Bet, Raise, Call, Fold };

class PokerHand {
public:
    std::string player;  // Player name
    std::string street;  // Street (e.g., 'preflop', 'flop', 'turn', 'river')
    Action action;       // Action taken by the player

    PokerHand(const std::string& player, const std::string& street, Action action);
};

double calculate_af(const std::vector<PokerHand>& hand_history, const std::string& player_name);
double calculate_vpip_percentage(const std::vector<PokerHand>& hand_history, const std::string& player_name);

#endif // POKER_STATS_HPP

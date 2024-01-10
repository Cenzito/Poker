#include "AnalysisDiego.hpp"


Hand::Hand(const std::string& player, const std::string& street, Action action)
    : player(player), street(street), action(action) {}


double calculate_af(const std::vector<Hand>& hand_history, const std::string& player_name) {
    int total_bets_raises = 0;
    int total_calls = 0;

    for (const auto& hand : hand_history) {
        if (hand.player == player_name) {
            if (hand.action == Bet || hand.action == Raise) {
                total_bets_raises++;
            } else if (hand.action == Call) {
                total_calls++;
            }
        }
    }

    double aggression_factor = (total_calls > 0) ? static_cast<double>(total_bets_raises) / total_calls : total_bets_raises;

    return aggression_factor;
}

double calculate_vpip_percentage(const std::vector<Hand>& hand_history, const std::string& player_name) {
    int total_hands = 0;
    int vpip_hands = 0;

    for (const Hand& hand : hand_history) {
        if (hand.player == player_name && hand.street == "preflop") {
            total_hands++;

            if (hand.action != Fold) {
                vpip_hands++;
            }
        }
    }

    double vpip_percentage = (total_hands > 0) ? static_cast<double>(vpip_hands) / total_hands : 0.0;

    return vpip_percentage * 100.0; // Convert to percentage
}


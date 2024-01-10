#include <iostream>
#include "AnalysisDiego.hpp"

int main() {
    // Sample data (replace this with your actual hand history data)
    std::vector<Hand> hand_history = { // HERE WE HAVE TO ADD OUR HANDS HISTORY, THAT WE EXTRACTED FROM POKERSTARS AND TURNED INTO A .TXT FILE.
        {"Player1", "preflop", Raise},
        {"Player2", "preflop", Fold},
        {"Player1", "flop", Bet},
        {"Player2", "flop", Call},
        // ... Add more hands as needed
    };

    // Replace "YourPlayerName" with your actual player name
    std::string your_player_name = "YourPlayerName";

    double af = calculate_af(hand_history, your_player_name);
    std::cout << "Your Aggression Factor is: " << af << std::endl;

    double vpip_percentage = calculate_vpip_percentage(hand_history, your_player_name);
    std::cout << "Your VPIP (Voluntarily Put In Pot) Percentage is: " << vpip_percentage << "%" << std::endl;

    return 0;
}

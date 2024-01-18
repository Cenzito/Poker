#include "vpip.h"

// Assuming you have a way to track total hands played and hands where the player put money voluntarily
int Hand = player_hands.size();
int handsPlayedVoluntarily = 0;

for (const Hand& hand : player_hands) {
    if (hand.action != "Fold" && hand.street == "Preflop") {
        handsPlayedVoluntarily++;
    }
}

double vpip = static_cast<double>(handsPlayedVoluntarily) / totalHandsPlayed * 100;
std::cout << "VPIP: " << vpip << "%" << std::endl;

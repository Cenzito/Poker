#include "poker_scratch.h"

#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include <vector>
#include <string>

class Logic_ {
public:
    PokerPlayer(const std::string& name, int initialChips);

    int getChips() const;
    void placeBet(int amount);
    void receiveCards(const std::vector<std::string>& cards);
    void showHand() const;
    void winChips(int amount);
    // Add more functions as needed

private:
    std::string name;
    int chips;
    std::vector<std::string> hand; // Represents the player's cards
    // Add more attributes as needed
};

#endif // POKER_PLAYER_HPP

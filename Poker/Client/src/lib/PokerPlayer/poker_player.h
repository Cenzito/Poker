#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include "card.h"

class PokerPlayer {
public:
    PokerPlayer(const std::string& name, int chips);
    void bet(int amount);
    void fold();
    bool folded();
    void receiveCard(const Card& card);
    std::string showHand() const;
    void addChips(int amount);
    void resetForNewRound();
    std::string get_username();
    std::string get_password();
    void set_username(std::string username);
    void set_password(std::string password);
    bool roundStarted;  

private:
    std::string username;
    std::string password;
    int chips;
    std::vector<Card> hand;
    bool isFolded;
    int currentBet;
};

#endif // POKERPLAYER_H

#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include <vector>
#include <string>
#include <set>
#include "table.hpp"
#include "Card.hpp"
#include <unordered_map>

//TO IMPLEMENT:
//Combinations class that gives which defines what combinations are possible and which are better than others
//add to game class a function that: given player cards and cards in the middle give their combination (and probablity of success later)




class PokerPlayer {
public:
    PokerPlayer(const std::string& name, int initialChips);
    const std::string& getName() const { return name; }
    static std::set<std::string> names;
    int getChips() const;
    void placeBet(int amount);
    void receiveCards(const std::vector<Card>& cards);
    void showHand() const;
    void winChips(int amount);
    void setPosition(int pos); // 1: UTG, 2: UTG+1 ...

    //this is not implemented in cpp file
    virtual void action(Table table, int minAmount, int type); // 1 = normal round, 2 = small blind, 3 = bigblind


protected:
    int position;
    std::string name;
    int chips;
    std::vector<Card> hand;
    bool isBot, isAllin, isFold;
};













#endif // POKER_PLAYER_HPP

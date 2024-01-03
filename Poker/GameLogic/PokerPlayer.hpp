#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include <vector>
#include <string>
#include <set>
#include "Table.hpp"
#include "Card.hpp"
#include <unordered_map>





class PokerPlayer {
public:
    PokerPlayer(const std::string& name);
    const std::string& getName() const;

    //Action functions call raise fold
    void call(int);
    void raise(int);
    void fold();

    //void receiveCards(const std::vector<Card>& cards);
    void showHand() const;
    bool canBet(int amount) const;
    int decideBet(int currentHighestBet, int money, int minimumRaise);

    //void receiveCards(const std::vector<Card>& hand);
    void updateTable(Table table);

    void receiveCards(const std::vector<Card> cards);
    void removeCards();
    std::vector<Card> getHand() const;

    Table tableInfo;

    //this is not implemented in cpp file
    //virtual void action(Table table, int minAmount, int type); // 1 = normal round, 2 = small blind, 3 = bigblind

    int chips;
    void updateChips();

    int bet = -2;

    std::string name;
    std::vector<Card> hand;
    //isActive tells if it's the players turn to bet
    bool isBot, isActive;
    
};







#endif // POKER_PLAYER_HPP

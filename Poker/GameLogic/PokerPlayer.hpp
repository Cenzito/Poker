#ifndef POKER_PLAYER_HPP
#define POKER_PLAYER_HPP

#include <vector>
#include <string>
#include <set>
#include "Table.hpp"
#include "Card.hpp"
#include <unordered_map>

//TO IMPLEMENT:
//Combinations class that gives which defines what combinations are possible and which are better than others
//add to game class a function that: given player cards and cards in the middle give their combination (and probablity of success later)
//implement betting in the game class
//A class Table that records all information on the table
//virtual std::pair<std::string, int> action(const Table* table, int minAmount, int type);




class PokerPlayer {
public:
    PokerPlayer(const std::string& name, int initialChips);
    const std::string& getName() const { return name; }
    void placeBet(int amount);
    void receiveCards(const std::vector<Card>& cards);
    void removeCards();

    std::vector<Card> getHand() const;

    void updateTable(Table table);

    //this is not implemented in cpp file
    //virtual void action(Table table, int minAmount, int type); // 1 = normal round, 2 = small blind, 3 = bigblind

    //Table tableInfo; //

protected:
    Table tableInfo;
    std::string name;
    std::vector<Card> hand;
    bool isBot, isAllin, isFold;
};







#endif // POKER_PLAYER_HPP

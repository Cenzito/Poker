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
    const std::string& getName() const;
    void placeBet(int amount);

    //Practical functions for betting round functions
    int get_bet() {return current_bet;}
    int get_chips() {return chips;}
    bool stopped_playing() {return isFold;}
    void make_bet_zero() {
        current_bet = 0;
    }
    void win(int pot) {
        chips += pot;
    }
    void will_restart_playing() {
        isFold = false;
    }
    //Action functions call raise fold
    void call(int);
    int raise(int);
    int fold();

    //void receiveCards(const std::vector<Card>& cards);
    void showHand() const;
    bool isActive() const;
    bool canBet(int amount) const;
    void bet(int amount);
    int decideBet(int currentHighestBet, int minimumRaise);
    //void receiveCards(const std::vector<Card>& hand);
    void updateTable(const Table& tableInfo);
    void updateTable(Table* table);

    //commented these 3 because of conflicts (delete and recreate pull request if this is unneccesary)
    void receiveCards(const std::vector<Card>& cards);
    void removeCards();
    std::vector<Card> getHand() const;


    //this is not implemented in cpp file
    //virtual void action(Table table, int minAmount, int type); // 1 = normal round, 2 = small blind, 3 = bigblind


    //Table tableInfo; //


protected:
    Table tableInfo;
    std::string name;
    std::vector<Card> hand;
    bool isBot, isAllin, isFold;
    int chips;
    int current_bet; //to be used to compare bets in round of betting functions
    bool active;
    Table currentTable;
    
};







#endif // POKER_PLAYER_HPP

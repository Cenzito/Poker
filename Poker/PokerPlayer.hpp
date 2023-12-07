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
    bool stopped_playing() {return isFold;} //will be used in round of betting

    std::vector<Card> getHand() const;

    void updateTable(Table table);

    void pay_blind(int blind) {
        initialChips -= blind;
        current_bet = blind;
    }

    void call(int);
        //decreases Chips available by bet_on_table - current_bet
        //changes current_bet = bet_on_table
    int raise(int);
        //decreases Chips available by amount_to_raise
        //changes current_bet = amount_to_raise + current_bet
        //returns new total bet
    int fold();
        //function used to zero bet on table to use at end of every round
        //change value of player_stopped_playing to true
        //returns current bet to add to total pot

    int bet_in_pot() {
        int current_bet_2 = current_bet; //allows us to make current bet 0 while returning current_bet_2
        current_bet = 0;
        return current_bet_2;
    }

    void win(int pot_won) {
        initialChips += pot_won;
    }

    //this is not implemented in cpp file
    //virtual void action(Table table, int minAmount, int type); // 1 = normal round, 2 = small blind, 3 = bigblind
    Table tableInfo;

protected:
    std::string name;
    std::vector<Card> hand;
    bool isBot, isAllin, isFold;
    int initialChips;
    int current_bet;
};







#endif // POKER_PLAYER_HPP

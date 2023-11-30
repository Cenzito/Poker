#ifndef TABLE_HPP
#define TABLE_HPP

#include "PokerPlayer.hpp"

//implement betting in the game class
class Table {
public:
    Table(std::vector<PokerPlayer> players);
    void resetBets();
    void addBet();

private:
    int pot;
    //hash map associating each player to his bet this round
    std::unordered_map < PokerPlayer, int > betAmounts;
};
#endif // TABLE_HPP

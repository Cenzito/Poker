#ifndef TABLE_HPP
#define TABLE_HPP

#include <unordered_map>

//implement betting in the game class
class Table {
public:
    Table(int players);
    void resetBets();
    void addBet();

private:
    int pot;
    //hash map associating each player to his bet this round
    std::unordered_map <int, int> betAmounts;
};
#endif // TABLE_HPP

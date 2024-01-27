#ifndef PLAYERINFO_H
#define PLAYERINFO_H


#include "GameLogic/Card.hpp"
#include <unordered_map>

#include <iostream>
#include <vector>


//public information about the player that will be stored in the Table class
class PlayerInfo
{
    public:
        PlayerInfo(std::string name, int stack_size, int bet = 0);
        PlayerInfo();
        std::string name;
        int stack_size;
        int bet;

        std::vector<Card> cards;

        bool isAllin, isFold;
        void Print();
        std::string player_name();

};

#endif // PLAYERINFO_H

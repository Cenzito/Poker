#ifndef PLAYERINFO_H
#define PLAYERINFO_H


#include <unordered_map>

#include <iostream>


//public information about the player that will be stored in the Table class
class PlayerInfo
{
    public:
        PlayerInfo(std::string name, int stack_size, int bet = 0);
        PlayerInfo();

        std::string name;
        int stack_size;
        int bet;

        bool isAllin, isFold;

};

#endif // PLAYERINFO_H

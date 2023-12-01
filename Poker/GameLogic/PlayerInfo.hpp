#ifndef PLAYERINFO_H
#define PLAYERINFO_H


#include <unordered_map>

#include <iostream>


//public information about the player that will be stored in the Table class
class PlayerInfo
{
    public:
        PlayerInfo(std::string name, int stack_size, int bet = 0);

        std::string get_name();
        int get_stack();
        int get_bet();
    private:
        std::string name;
        int stack_size;
        int bet;

};

#endif // PLAYERINFO_H

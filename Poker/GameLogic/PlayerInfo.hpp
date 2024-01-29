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
        std::string name; //represents the name of the Player
        int stack_size; //represents the total amount of chips left to the player
        int bet; //represents the bet that the player makes

        std::vector<Card> cards; //attribute that keeps the cards of the player

        bool isAllin, isFold; //booleans used for identifying players that fold or are all-in
        void Print(); //a function that prints all data members of a player, used for debugging

};

#endif // PLAYERINFO_H

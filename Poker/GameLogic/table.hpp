#ifndef TABLE_HPP
#define TABLE_HPP

#include <unordered_map>

#include <iostream>
#include <vector>
#include "PlayerInfo.hpp"
#include "Card.hpp"

//This is an object that will be passed to every player every time a change is made
//It contains public information that every player should know
class Table {
public:
    //constructors
    Table(int seats);
    Table(); //default 5 seats

    void Print();

    //Card information
    std::vector<Card> communityCards; //Cards that anyone can see

    //Player information
    int seats; //max number of players at table
    int player_num; //current number of players
    int current_player;
    int ButtonPlayer; //0 set as the button initially, so 1 is small blind, 2 is big blind, 3 is under the gun etc and then alternates
    std::unordered_map <int, PlayerInfo> playerInfo; //hash map associating each position to the player there (playerInfo[0] is the first player that joined)

    //Money information
    int SBValue;
    int BBValue;

    int pot;

    int bet_on_table; //Used to see if players have matched the bet required to call

    //hash map associating each position to the player there
    //position is just their placement at the table (not BB, SB...)
    std::unordered_map <int, PlayerInfo> playerInfo;
};

#endif // TABLE_HPP

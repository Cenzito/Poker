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
    Table(int seats);
    //default to 5 players
    Table();

    //Cards that anyone can see
    std::vector<Card> communityCards;

    //max number of players at table
    int seats;
    //current number of players
    int player_num;
    int pot;
    int current_player;

    int smallBlindPlayer;

    int SBValue;
    int BBValue;

    //hash map associating each position to the player there
    //position is just their placement at the table (not BB, SB...)
    std::unordered_map <int, PlayerInfo> playerInfo;
};

#endif // TABLE_HPP

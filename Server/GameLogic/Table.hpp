#ifndef TABLE_HPP
#define TABLE_HPP

#include <unordered_map>

#include <iostream>
#include <vector>
#include "PlayerInfo.hpp"
#include "Card.hpp"


enum class CommandType {
    Bet,
    SetBiggestBet,
    SetLastRaiser,
    Win,
    AllIn,
    Fold,
    SetActivePlayer,
    AddCardMid,
    NextRound,
    ResetGame,
    JoinGame,
    SetPlayerInfo,
    SetCards,
    Invalid
};


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
    int active_players(); //returns number of non folded players
    int current_player;
    int ButtonPlayer; //0 set as the button initially, so 1 is small blind, 2 is big blind, 3 is under the gun etc and then alternates
    std::unordered_map <int, PlayerInfo> playerInfo; //hash map associating each position to the player there (playerInfo[0] is the first player that joined)
    int playerIndex(std::string& name); //returns the index of the player in the playerInfo unordered map

    //Money information
    int SBValue;
    int BBValue;

    int pot;
    std::unordered_map <int, int> subpots;

    //usefull variables for betting round
    int betting_round; //current betting round (0: preflop, 1: river...)
    int current_biggest_bet; //biggest bet of the betting round
    int lastRaiser; //last person to raise ( if get back to him, we end betting round )


    void updateTable(std::string command);
    CommandType parseCommand(const std::string& command);
    PlayerInfo* getPlayerInfo(std::string name);

};

#endif // TABLE_HPP

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>

#include "./PokerPlayer.hpp"
#include "Deck.hpp"
#include "table.hpp"
#include "PokerPlayer.hpp"
#include "PlayerInfo.hpp"
#include "./Bots/Bot.hpp"

class Game {
public:
    Game(int numOfPlayers);
    void JoinGame(PokerPlayer);

    void startGame();
    void updateTable(const Table& tableInfo);



protected:
    void pay(PokerPlayer player, int sum);
    void win(PokerPlayer player, int sum);

    void update();
    void bettingRound();
    bool isRoundOver() const;


    void turn(int index_turn, PokerPlayer player);
    void round_of_betting(int index_turn);
    void end_round();


    void startRound();
    void addBot(PokerPlayer bot);

    //start a new hand
    void nextHand();
    void addBet(int pos, int amount);
    void winMoney(int pos, int amount);
    int getFreeSeat();
    void addCard(Card card);
    void leaveGame(PokerPlayer);


    Deck deck;
    Table tableInfo;

    //would need to change this to hold player name and way to communicate with them (through server)
    std::vector<PokerPlayer> players;
    int currentHighestBet;
    int minimumRaise;

    //Following used to determine when to go to next stages of a round (turn, flop, river)
    int players_standing; //players_standing (if players_standing == 1 then round ends as 1 winner)
    int number_callers; //starts at 0 at the start of every raise, etc. check round() function
    int small_blind_index; //very useful to determine which player has small and big blind in any round
    int index_turn; //Will be used to just shift from one player to the other as Players are in a vector
    int bet_on_table; //Used to see if players have matched the bet required to call
};


#endif // GAME_HPP

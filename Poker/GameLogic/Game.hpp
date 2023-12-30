#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>

#include "./PokerPlayer.hpp"
#include "Deck.hpp"
#include "table.hpp"
#include "PlayerInfo.hpp"
#include "./Bots/Bot.hpp"


enum Action { //will be used for implementation of turn()
    call,
    raise_,
    fold
};

class Game {
public:
    Game(int numOfPlayers);
    //void JoinGame(PokerPlayer);

    void startGame();
    void updateTable(const Table& tableInfo);



protected:

    Action AskAction(PokerPlayer);

    void pay(PokerPlayer player, int sum);
    void win(PokerPlayer player, int sum);

    void update();
    void bettingRound();
    bool isRoundOver() const;


    void turn(int turn_index, PokerPlayer player);
    //void bettingRound(int first_player, bool isfirst_round);
    void end_round();


    void startRound();
    void ChangeRound();
    //void addBot(PokerPlayer bot);

    //start a new hand
    void DealCards();
    void nextHand();
    void addBet(int pos, int amount);
    void winMoney(int pos, int amount);
    //int getFreeSeat();
    void addCard(Card card);
    void leaveGame(PokerPlayer);


    Deck deck;
    Table tableInfo;

    //would need to change this to hold player name and way to communicate with them (through server)
    std::vector<PokerPlayer> players;

};

#endif // GAME_HPP

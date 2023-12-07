#ifndef GAME_HPP
#define GAME_HPP

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
    void startRound();

    void addBot(PokerPlayer bot);

    //start a new hand
    void nextHand();


    void addBet(int pos, int amount);
    void winMoney(int pos, int amount);

    int getFreeSeat();

    void addCard(Card card);



    void leaveGame(PokerPlayer);   
private:
    void update();
    Deck deck;
    Table tableInfo;
    std::vector<PokerPlayer> players;
};


#endif // GAME_HPP

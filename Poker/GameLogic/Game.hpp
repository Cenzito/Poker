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

    void startGame();
    void updateTable(const Table& tableInfo);

    void addBot(PokerPlayer bot);

private:
    void update();
    void bettingRound();
    bool isRoundOver() const;


  // commented this because of conflict (delete and recreate pull request if this is unneccesary)
    void startRound();

    //start a new hand
    void nextHand();
    void addBet(int pos, int amount);
    void winMoney(int pos, int amount);
    int getFreeSeat();
    void addCard(Card card);
    void leaveGame(PokerPlayer);   


    Deck deck;
    Table tableInfo;
    std::vector<PokerPlayer> players;
    int currentHighestBet;
    int minimumRaise;
};


#endif // GAME_HPP

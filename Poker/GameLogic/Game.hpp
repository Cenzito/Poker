#ifndef GAME_HPP
#define GAME_HPP

#include "./PokerPlayer.hpp"
#include "Deck.hpp"
#include "table.hpp"
#include "PokerPlayer.hpp"
#include "PlayerInfo.hpp"

class Game {
public:
    Game(int numOfPlayers);
    void JoinGame(PokerPlayer);
    void startGame();
    void updateTable(const Table& tableInfo);



private:
    void update();
    void bettingRound();
    bool isRoundOver() const;

    Deck deck;
    Table tableInfo;
    std::vector<PokerPlayer> players;
    int currentHighestBet;
    const int minimumRaise;
};


#endif // GAME_HPP

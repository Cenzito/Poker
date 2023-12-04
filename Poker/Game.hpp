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

    void update();
private:
    Deck deck;
    Table tableInfo;
    std::vector<PokerPlayer> players;
};


#endif // GAME_HPP

#ifndef GAME_HPP
#define GAME_HPP

#include "./PokerPlayer.hpp"
#include "Deck.hpp"

class Game {
public:
    Game(int numOfPlayers);
    void startGame();

private:
    Deck deck;
    std::vector<PokerPlayer> players;
    std::vector<Card> communityCards;
};


#endif // GAME_HPP

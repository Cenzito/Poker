#ifndef GAMELOCAL_HPP
#define GAMELOCAL_HPP

#include "Game.hpp"



class GameLocal : public Game
{
public:
    GameLocal();

    void JoinGame(PokerPlayer);
    void addBot(PokerPlayer bot);
    void pay(int position, int sum);
    void win(int position, int sum);

    void updatePlayersTable();

    void nextHand();

    //would need to change this to hold player name and way to communicate with them (through server)
    std::vector<PokerPlayer> players;
};

#endif // GAMELOCAL_HPP

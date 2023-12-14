#ifndef GAMELOCAL_HPP
#define GAMELOCAL_HPP

#include "Game.hpp"
#include "PokerPlayerLocal.hpp"


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

    std::vector<PokerPlayer> players;
};

#endif // GAMELOCAL_HPP

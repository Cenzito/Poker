#ifndef GAMELOCAL_HPP
#define GAMELOCAL_HPP

#include "Game.hpp"
#include "PokerPlayerLocal.hpp"
#include "Table.hpp"


class GameLocal : public Game
{
public:
    GameLocal(std::vector<PokerPlayer> players);
    void testGameLocal(int num_rounds);
    void JoinGame(PokerPlayer);
    void addBot(PokerPlayer bot);
    void pay(int position, int sum);
    void win(int position, int sum);
    void updatePlayersTable();
    void nextHand();

    Table table;
    std::vector<PokerPlayer> players;
};

#endif // GAMELOCAL_HPP

#ifndef GAMELOCAL_HPP
#define GAMELOCAL_HPP

#include "Game.hpp"
#include "PokerPlayerLocal.hpp"
#include "Table.hpp"


class GameLocal : public Game
{
public:
    GameLocal(int seats);
    void testGameLocal(int num_rounds);
    void JoinGame(PokerPlayerLocal);
    void addBot(PokerPlayerLocal bot);
    //actions on the player
    void pay(PlayerInfo& PlayerPay, int sum);
    void win(PlayerInfo& PlayerWin, int sum);
    void fold(PlayerInfo& foldPlayer);

    void endHand(PlayerInfo& winner);

    void updatePlayersTable();
    void nextHand();

    signed int askAction(PokerPlayerLocal player);
    void bettingRound(int first_player, bool isfirst_round);

    PokerPlayerLocal findPlayer(std::string name);
    std::vector<PokerPlayerLocal> players;

    bool hand_finished;
};

#endif // GAMELOCAL_HPP

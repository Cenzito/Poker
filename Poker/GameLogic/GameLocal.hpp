#ifndef GAMELOCAL_HPP
#define GAMELOCAL_HPP

#include "PokerPlayerLocal.hpp"
#include "Table.hpp"
#include "Deck.hpp"
#include "../Bots/Bot.hpp"
#include "PokerHand.hpp"
#include <algorithm>


class GameLocal
{
public:
    GameLocal(int seats);

    void StartGame();


    void JoinGame(PokerPlayerLocal);
    void addBot(Bot bot);
    int getFreeSeat();

    //actions on the player
    void pay(PlayerInfo& PlayerPay, int sum);
    void win(PlayerInfo& PlayerWin, int sum);
    void fold(PlayerInfo& foldPlayer);

    void endHand(PlayerInfo& winner);
    void newHand();

    void updatePlayersTable();
    void nextHand();

    signed int askAction(PokerPlayerLocal player);
    void bettingRound(int first_player, bool isfirst_round);

    PokerPlayerLocal findPlayer(std::string name);
    std::vector<PokerPlayerLocal> players;

    Deck deck;
    Table tableInfo;

    int players_standing;
    bool hand_finished;
};

#endif // GAMELOCAL_HPP

#ifndef GAMELOCAL_HPP
#define GAMELOCAL_HPP

#include "PokerPlayer.hpp"
#include "Table.hpp"
#include "Deck.hpp"
#include "../Bots/Bot.hpp"
#include "PokerHand.hpp"
#include <QObject>
#include <QTimer>
#include <algorithm>
#include <QSignalMapper>


class GameLocal : public QObject
{
    Q_OBJECT
public:
    GameLocal(int seats);


    void JoinGame(PokerPlayer*);
    void addBot(Bot* bot);
    int getFreeSeat();

    //actions on the player
    void pay(PlayerInfo& PlayerPay, int sum);
    void win(PlayerInfo& PlayerWin, int sum);
    void fold(PlayerInfo& foldPlayer);
    void LeaveTable(PlayerInfo& Player, int pos);
    void endHand(PlayerInfo& winner);


    void nextHand();


    void nextBettingRound();

    void setNextCurrentPlayer();

    PokerPlayer* findPlayer(std::string name);
    std::vector<PokerPlayer*> players;

    Deck deck;
    Table tableInfo;

    int players_standing;
    bool hand_finished;

    void askBet(PokerPlayer* p);
    void onAction();

public slots:
    void onRaise(int amount);
    void onFold();
    void onCall();

    void updatePlayersTable();

signals:
    void updatePTable(Table t);
    void askAction();
};

#endif // GAMELOCAL_HPP

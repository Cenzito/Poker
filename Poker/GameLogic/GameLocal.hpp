#ifndef GAMELOCAL_HPP
#define GAMELOCAL_HPP

#include "PokerPlayer.hpp"
#include "Table.hpp"
#include "Deck.hpp"
#include "../Bots/Bot.hpp"
#include "../Bots/Hard/Darius/BotDarius.hpp"
#include "PokerHand.hpp"
#include <QObject>
#include <QTimer>
#include <algorithm>
#include "Card.hpp"
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
    void allin(PlayerInfo& allinPlayer);

    //end of game functions
    void endHand();
    void distribute();
    std::vector<PlayerInfo> winners();
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

    void updatePlayersTable(std::string);
    void setPlayerInfos(PokerPlayer* player);

signals:
    void updatePTable(std::string command);
    void setPInf(std::string command);

    void askAction();

};

#endif // GAMELOCAL_HPP

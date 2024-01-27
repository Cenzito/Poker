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
#include <QSignalMapper>


class GameLocal : public QObject
{
    Q_OBJECT
public:
    //constructor
    GameLocal(int seats);

    //adding players
    int getFreeSeat();
    void JoinGame(PokerPlayer*);
    void addBot(Bot* bot);

    //actions on the player
    void pay(PlayerInfo& PlayerPay, int sum);
    void win(PlayerInfo& PlayerWin, int sum);
    void fold(PlayerInfo& foldPlayer);
    void allin(PlayerInfo& allinPlayer);
    PokerPlayer* findPlayer(std::string name);

    //end of game functions
    void endHand();
    void distribute();
    std::vector<PlayerInfo> winners();
    void nextHand();

    //round management functions
    void nextBettingRound();
    void setNextCurrentPlayer();

    //important variables
    Deck deck;
    Table tableInfo;
    int players_standing;
    int players_all_in;
    bool hand_finished;
    std::vector<PokerPlayer*> players;

    //action control
    void askBet(PokerPlayer* p);
    void onAction();


public slots:
    //action control
    void onRaise(int amount);
    void onFold();
    void onCall();

    //information control
    void updatePlayersTable(std::string);
    void setPlayerInfos(PokerPlayer* player);

signals:
    //more information control
    void updatePTable(std::string command);
    void setPInf(std::string command);

    //more action control
    void askAction();

};

#endif // GAMELOCAL_HPP

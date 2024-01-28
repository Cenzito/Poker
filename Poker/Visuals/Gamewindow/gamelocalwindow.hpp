#ifndef GAMELOCALWINDOW_HPP
#define GAMELOCALWINDOW_HPP

#include "GameLogic/GameLocal.hpp"
#include "sqlite3.h"
#include "/Database/Creationaccount.hpp"
#include "PokerPlayer.hpp"
#include "Client/client.h"
#include "gamewindow.hpp"


class GameLocalWindow : public GameWindow
{
public:
    explicit GameLocalWindow(QWidget *parent = nullptr, std::string p = "name", PokerClient pokerclient = PokerClient(server_ip, port));

    GameLocal game;

    PokerClient pokerclient;

    CreationAccount account = CreationAccount("Account.db");

    std::string username,password;

    std::string server_ip;

    int port;

private:

    void onRaiseButtonClicked() override;

    void onCallButtonClicked() override;

    void onFoldButtonClicked() override;

    void onPlayButtonClicked() override;

    void on_pushButton_signin_clicked() override;

    void on_pushButton_login_clicked() override;

    
};

#endif // GAMELOCALWINDOW_HPP

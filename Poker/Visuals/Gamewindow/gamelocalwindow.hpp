#ifndef GAMELOCALWINDOW_HPP
#define GAMELOCALWINDOW_HPP

#include "GameLogic/GameLocal.hpp"
#include "sqlite3.h"
#include "Database/Creationaccount.hpp"
#include "PokerPlayer.hpp"
#include "Client/client.h"
#include "gamewindow.hpp"


class GameLocalWindow : public GameWindow
{
public:
    explicit GameLocalWindow(QWidget *parent = nullptr, std::string p = "name");

    GameLocal game;

    CreationAccount account = CreationAccount("Account.db");

    PokerClient pokerclient = PokerClient(server_ip, port);

    std::string username,password;

    const std::string server_ip;

    int port;

private:

    void onRaiseButtonClicked() override;

    void onCallButtonClicked() override;

    void onFoldButtonClicked() override;

    void onPlayButtonClicked() override;

    void on_pushButton_signin_clicked() override;

    void on_pushButton_login_clicked() override;

    void switch_bet_button_on() override;

    void switch_bet_button_off() override;

    
};

#endif // GAMELOCALWINDOW_HPP

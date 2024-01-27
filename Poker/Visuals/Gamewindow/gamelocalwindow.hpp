#ifndef GAMELOCALWINDOW_HPP
#define GAMELOCALWINDOW_HPP

#include "gamewindow.hpp"
#include "GameLogic/GameLocal.hpp"
#include "sqlite3.h"
#include "Creationaccount.hpp"
#include "PokerPlayer.hpp"


class GameLocalWindow : public GameWindow
{
public:
    explicit GameLocalWindow(QWidget *parent = nullptr, std::string p = "name");

    GameLocal game;

    PokerClient pokerclient;

    CreationAccount account = CreationAccount("Account.db");

    string username,password;
private:
    void onRaiseButtonClicked() override;

    void onCallButtonClicked() override;

    void onFoldButtonClicked() override;

    void onPlayButtonClicked() override;

    void on_pushButton_login_clicked() override;

    
};

#endif // GAMELOCALWINDOW_HPP

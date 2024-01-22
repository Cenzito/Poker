#ifndef GAMELOCALWINDOW_HPP
#define GAMELOCALWINDOW_HPP

#include "gamewindow.hpp"
#include "GameLogic/GameLocal.hpp"
#include "sqlite3.h"


class GameLocalWindow : public GameWindow
{
public:
    explicit GameLocalWindow(QWidget *parent = nullptr, std::string p = "name");

    GameLocal game;

    PokerClient pokerclient;

    Creationaccount account = CreationAccount("Account.db");
private:
    void onRaiseButtonClicked() override;

    void onCallButtonClicked() override;

    void onFoldButtonClicked() override;

    void onPlayButtonClicked() override;

    void on_pushButton_login_clicked() override;

    
};

#endif // GAMELOCALWINDOW_HPP

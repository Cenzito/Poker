#include "gamelocalwindow.hpp"
#include "ruleswindow.h"
#include <qdebug.h>
#include "client.h"
#include "Creationaccount.hpp"
#include "PokerPlayer.hpp"


GameLocalWindow::GameLocalWindow(QWidget *parent, std::string p) : GameWindow(parent, p), game(7)
{
    //make player join the game
    //qDebug() << QString::fromStdString(game_player.getName());


    game.JoinGame(&game_player);

}


void GameLocalWindow::onPlayButtonClicked(){
    RulesWindow *rulesWindow = new RulesWindow(this) ;
    rulesWindow->show();
}

void GameLocalWindow::on_pushButton_login_clicked(){

    const char* sql = "CREATE TABLE IF NOT EXISTS ACCOUNT("
                  "USERNAME TEXT PRIMARY KEY NOT NULL, "
                  "PASSWORD TEXT NOT NULL);";
    account.CreationTable(sql);

    Qstring user = ui->lineEdit_user->text();
    Qstring pass = ui->lineEdit_pass->text();

    if(account.login(user, pass)){
        this->username = user;
        this->password = pass;
        PokerClient pokerclient = PokerClient(server_ip, port);
        pokerclient.sendMessage(user + ":" + pass);
    }
}

void GameLocalWindow::on_pushButton_signin_clicked(){
    
    const char* sql = "CREATE TABLE IF NOT EXISTS ACCOUNT("
                  "USERNAME TEXT PRIMARY KEY NOT NULL, "
                  "PASSWORD TEXT NOT NULL);";
    get_account(this->account).CreationTable(sql);

    Qstring user = ui->lineEdit_newuser->text();
    Qstring pass = ui->lineEdit_newpass->text();

    if(account.Check_repetition(user)){
        account.Insertaccount(user, pass);
        this->username = user;
        this->password = pass;
        pokerclient = PokerClient(server_ip, port);
    }
}

void GameLocalWindow::onRaiseButtonClicked() {
    std::string message = "/raise";
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));
    qDebug() << add_bet;
    int sum = add_bet + current;
    //emit game_player.Raise(add_bet);
    if(sum <= account.get_money(account.get_db(), this->username)){
        ui.switch_bet_button_on()
        pokerclient.sendMessage(message + "" + std::to_string(sum));
        pokerclient.processUserInput(message + "" + sum, message);
    }
    else{
        ui.switch_bet_button_off();
    }
}

void GameLocalWindow::onCallButtonClicked(){ //Reminder: this is check/call button, need to work on changing the name in accordance with the situation, but functionallity should work fine for now
    //emit game_player.Call();
    int current = (ui->cumulative_bet_line->text()).toInt();
    std::string message = "/bet";
        if(current <= account.get_money(account.get_db(), this->username)){
        ui.switch_bet_button_on();
        pokerclient.sendMessage(message + "" + std::to_string(current));
        pokerclient.processUserInput(message + "" + current, message);
    }
    else{
        ui.switch_bet_button_off();
    }
    pokerclient.sendMessage(message);
    pokerclient.processUserInput(message);
}



void GameLocalWindow::onFoldButtonClicked(){
    //emit game_player.Fold();
    std::string message = "fold";
    pokerclient.sendMessage(message);
    pokerclient.processUserInput(message);
}

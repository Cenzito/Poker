#include "gamelocalwindow.hpp"
#include "ruleswindow.h"
#include "gamewindow.cpp"
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

void GameLocalWindow::on_pushButton_login_clicked(){

    const char* sql = "CREATE TABLE IF NOT EXISTS ACCOUNT("
                  "USERNAME TEXT PRIMARY KEY NOT NULL, "
                  "PASSWORD TEXT NOT NULL);";
    account.CreationTable(sql);

    QString user = ui->lineEdit_user->text();
    QString pass = ui->lineEdit_pass->text();

    if(account.login(user, pass)){
        this->username = user.toStdString();
        this->password = pass.toStdString();
        PokerClient pokerclient = PokerClient(server_ip, port);
        pokerclient.sendMessage(user.toStdString() + ":" + pass.toStdString());
        pokerclient.player.set_name(user.toStdString());
    }
    else{
        pokerclient.sendMessage("/quit");
        pokerclient.send_message = "/quit";
    }
}

void GameLocalWindow::on_pushButton_signin_clicked(){
    
    const char* sql = "CREATE TABLE IF NOT EXISTS ACCOUNT("
                  "USERNAME TEXT PRIMARY KEY NOT NULL, "
                  "PASSWORD TEXT NOT NULL);";
    get_account(this->account).CreationTable(sql);

    QString user = ui->lineEdit_newuser->text();
    QString pass = ui->lineEdit_newpass->text();

    if(account.Check_repetition(user)){
        account.Insertaccount(user, pass);
        this->username = user.toStdString();
        this->password = pass.toStdString();
        PokerClient pokerclient = PokerClient(server_ip, port);
    }
    else{
        pokerclient.sendMessage("/quit");
        pokerclient.send_message = "quit";
    }
}

void GameLocalWindow::onRaiseButtonClicked() {
    std::string message = "/raise";
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));
    qDebug() << add_bet;
    int sum = add_bet + current;
    if(sum <= account.get_money(account.get_db(), this->username)){
        switch_bet_button_on();
        pokerclient.sendMessage(message + "" + std::to_string(sum));
        pokerclient.send_message = message;
    }
    else{
        switch_bet_button_off();
    }
}

void GameLocalWindow::onCallButtonClicked(){ //Reminder: this is check/call button, need to work on changing the name in accordance with the situation, but functionallity should work fine for now
    //emit game_player.Call();
    int current = (ui->cumulative_bet_line->text()).toInt();
    std::string message = "/bet";
    if(current <= account.get_money(account.get_db(), this->username)){
        switch_bet_button_on();
        pokerclient.sendMessage(message + "" + std::to_string(current));
        pokerclient.send_message = message;
    }
    else{
        switch_bet_button_off();
    }
    pokerclient.send_message = "quit";
}



void GameLocalWindow::onFoldButtonClicked(){
    std::string message = "/fold";
    pokerclient.sendMessage(message);
    pokerclient.send_message = message;
}

/*
 * switch_bet_button_on() : display the bet button when it is our turn to bet
 *
*/
void GameLocalWindow::switch_bet_button_on(){
    ui->RaiseButton->show();
    ui->FoldButton->show() ;
    ui->CallButton->show();
}

/*
 * switch_bet_button_off() : remove display of the bet button when it is clicked
 *
*/

void GameLocalWindow::switch_bet_button_off(){
    ui->RaiseButton->hide();
    ui->FoldButton->hide() ;
    ui->CallButton->hide();
}

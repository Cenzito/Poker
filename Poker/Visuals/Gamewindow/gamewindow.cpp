    #include "gamewindow.hpp"
#include "Visuals/RulesWindow/ruleswindow.h"
#include "ui_gamewindow.h"
#include <QPixmap>
#include "GameLogic/table.hpp"
#include"GameLogic/PlayerInfo.hpp"
#include "GameLogic/PokerPlayer.hpp"
#include "GameLogic/Game.hpp"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &GameWindow::onPlayButtonClicked);

    QImage table_background(":/images/table.png");
    QSize table_background_size = ui->label_table->size();
    ui->label_table->setPixmap(QPixmap::fromImage(table_background).scaled(table_background_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

GameWindow::~GameWindow()
{
    delete ui;
}

const QString GameWindow::Get_image_path(const std::string &suit, const std::string &value, bool back){

    if (back){
        return ":/images/cards/back_card.png";
    }

    std::string temp =  ":/images/cards/"+suit+"/"+value+".png";
    QString final = QString::fromStdString(temp);
    return final;

}
void GameWindow::on_dealButton_clicked() {;}


    // see with logic to run from here the function that deals the cards and then return which ones we need to display

    //QImage card_1(GameWindow::Get_image_path("H", "1")); // simply change the arguments to get the card you want
    //QImage card_2(GameWindow::Get_image_path("D", "1")); // simply change the arguments to get the card you want


    //QSize size = ui->label_card1->size();

    //ui->label_card1->setPixmap(QPixmap::fromImage(card_1).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this
    //ui->label_card2->setPixmap(QPixmap::fromImage(card_2).scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // dont change this



void GameWindow::onPlayButtonClicked()
{
    RulesWindow *rulesWindow = new RulesWindow(this) ;
    rulesWindow->show();
}

void GameWindow::onRaiseButtonClicked()
{
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));
}

void GameWindow::update_to_display(PokerPlayer* player){

    game_player = player;

    GameWindow::display_names_bet(player);

}

void GameWindow::update_from_display(PokerPlayer* player){
    game_player = player;

    //If any button is pressed from the display, activate this function
    // link call/raise/fold with turn in game.cpp
}




// Minor functions used for updates :

void GameWindow::display_names_bet(PokerPlayer* player){

    if (player->tableInfo.player_num<=1) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
    }
    if (player->tableInfo.player_num<=2) {
        std::string playerName2 = player->tableInfo.playerInfo[1].name;
        ui ->line_player2->setText(QString::fromStdString(playerName2));
    }
    if (player->tableInfo.player_num<=3) {

        std::string playerName3 = player->tableInfo.playerInfo[2].name;
        ui ->line_player3->setText(QString::fromStdString(playerName3));
    }
    if (player->tableInfo.player_num<=4) {
        std::string playerName4 = player->tableInfo.playerInfo[3].name;
        ui ->line_player4->setText(QString::fromStdString(playerName4));
    }
    if (player->tableInfo.player_num<=5) {
        std::string playerName5 = player->tableInfo.playerInfo[4].name;
        ui ->line_player5->setText(QString::fromStdString(playerName5));
    }
    if (player->tableInfo.player_num<=6) {
        std::string playerName6 = player->tableInfo.playerInfo[5].name;
        ui ->line_player6->setText(QString::fromStdString(playerName6));
    }
    if (player->tableInfo.player_num<=7) {
        std::string playerName7 = player->tableInfo.playerInfo[6].name;
        ui ->line_player7->setText(QString::fromStdString(playerName7));
    }
    if (player->tableInfo.player_num<=8) {
        std::string playerName8 = player->tableInfo.playerInfo[7].name;
        ui ->line_player8->setText(QString::fromStdString(playerName8));
    }
}
// beginning of switch from name tag to bank display

void GameWindow::on_line_player1_cursorPositionChanged()
{
    QString text_line = ui->line_player1->text();
    std::string text = text_line.toStdString();

    std::string name = game_player->tableInfo.playerInfo[0].name;
    std::string stack =  std::to_string(game_player->tableInfo.playerInfo[0].stack_size);

    if (text == stack){
        QString name_qt = QString::fromStdString(name);
        ui->line_player1->setText(name_qt);
    }
    else {
        QString stack_qt = QString::fromStdString(stack);
        ui->line_player1->setText(stack_qt);
    }
}
void GameWindow::on_line_player2_cursorPositionChanged()
{
    if (game_player->tableInfo.player_num >= 2){
        QString text_line = ui->line_player2->text();
        std::string text = text_line.toStdString();

        std::string name = game_player->tableInfo.playerInfo[1].name;
        std::string stack =  std::to_string(game_player->tableInfo.playerInfo[1].stack_size);

        if (text == stack){
            QString name_qt = QString::fromStdString(name);
            ui->line_player2->setText(name_qt);
        }
        else {
            QString stack_qt = QString::fromStdString(stack);
            ui->line_player2->setText(stack_qt);
        }
    }

}
void GameWindow::on_line_player3_cursorPositionChanged()
{
    if (game_player->tableInfo.player_num >= 3){
        QString text_line = ui->line_player3->text();
        std::string text = text_line.toStdString();

        std::string name = game_player->tableInfo.playerInfo[2].name;
        std::string stack =  std::to_string(game_player->tableInfo.playerInfo[2].stack_size);

        if (text == stack){
            QString name_qt = QString::fromStdString(name);
            ui->line_player3->setText(name_qt);
        }
        else {
            QString stack_qt = QString::fromStdString(stack);
            ui->line_player3->setText(stack_qt);
        }
    }
}
void GameWindow::on_line_player4_cursorPositionChanged()
{
    if (game_player->tableInfo.player_num >= 4){
        QString text_line = ui->line_player4->text();
        std::string text = text_line.toStdString();

        std::string name = game_player->tableInfo.playerInfo[3].name;
        std::string stack =  std::to_string(game_player->tableInfo.playerInfo[3].stack_size);

        if (text == stack){
            QString name_qt = QString::fromStdString(name);
            ui->line_player4->setText(name_qt);
        }
        else {
            QString stack_qt = QString::fromStdString(stack);
            ui->line_player4->setText(stack_qt);
        }
    }
}
void GameWindow::on_line_player5_cursorPositionChanged()
{
    if (game_player->tableInfo.player_num >= 5){
        QString text_line = ui->line_player5->text();
        std::string text = text_line.toStdString();

        std::string name = game_player->tableInfo.playerInfo[4].name;
        std::string stack =  std::to_string(game_player->tableInfo.playerInfo[4].stack_size);

        if (text == stack){
            QString name_qt = QString::fromStdString(name);
            ui->line_player5->setText(name_qt);
        }
        else {
            QString stack_qt = QString::fromStdString(stack);
            ui->line_player5->setText(stack_qt);
        }
    }
}
void GameWindow::on_line_player6_cursorPositionChanged()
{
    if (game_player->tableInfo.player_num >= 6){
        QString text_line = ui->line_player6->text();
        std::string text = text_line.toStdString();

        std::string name = game_player->tableInfo.playerInfo[5].name;
        std::string stack =  std::to_string(game_player->tableInfo.playerInfo[5].stack_size);

        if (text == stack){
            QString name_qt = QString::fromStdString(name);
            ui->line_player6->setText(name_qt);
        }
        else {
            QString stack_qt = QString::fromStdString(stack);
            ui->line_player6->setText(stack_qt);
        }
    }
}
void GameWindow::on_line_player7_cursorPositionChanged()
{
    if (game_player->tableInfo.player_num >= 7){
        QString text_line = ui->line_player7->text();
        std::string text = text_line.toStdString();

        std::string name = game_player->tableInfo.playerInfo[6].name;
        std::string stack =  std::to_string(game_player->tableInfo.playerInfo[6].stack_size);

        if (text == stack){
            QString name_qt = QString::fromStdString(name);
            ui->line_player7->setText(name_qt);
        }
        else {
            QString stack_qt = QString::fromStdString(stack);
            ui->line_player7->setText(stack_qt);
        }
    }
}
void GameWindow::on_line_player8_cursorPositionChanged()
{
    if (game_player->tableInfo.player_num == 8){
        QString text_line = ui->line_player8->text();
        std::string text = text_line.toStdString();

        std::string name = game_player->tableInfo.playerInfo[7].name;
        std::string stack =  std::to_string(game_player->tableInfo.playerInfo[7].stack_size);

        if (text == stack){
            QString name_qt = QString::fromStdString(name);
            ui->line_player8->setText(name_qt);
        }
        else {
            QString stack_qt = QString::fromStdString(stack);
            ui->line_player8->setText(stack_qt);
        }
    }
}

// end of switch from name tag to bank display






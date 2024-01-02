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

void GameWindow::onPlayButtonClicked()
{
    RulesWindow *rulesWindow = new RulesWindow(this) ;
    rulesWindow->show();
}

void GameWindow::on_BetButton_clicked()
{
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));
}

void GameWindow::update_to_display(PokerPlayer* player){

    if (player->tableInfo.player_num<=1) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        int playerbet1 = player->tableInfo.playerInfo[0].bet;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
        ui->line_bet1->setText(QString::fromStdString(std::to_string(playerbet1)));
    }

    if (player->tableInfo.player_num<=2) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        std::string playerName2 = player->tableInfo.playerInfo[1].name;
        int playerbet1 = player->tableInfo.playerInfo[0].bet;
        int playerbet2 = player->tableInfo.playerInfo[1].bet;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
        ui ->line_player2->setText(QString::fromStdString(playerName2));
        ui->line_bet1->setText(QString::fromStdString(std::to_string(playerbet1)));
        ui->line_bet2->setText(QString::fromStdString(std::to_string(playerbet2)));
    }

    if (player->tableInfo.player_num<=3) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        std::string playerName2 = player->tableInfo.playerInfo[1].name;
        std::string playerName3 = player->tableInfo.playerInfo[2].name;
        int playerbet1 = player->tableInfo.playerInfo[0].bet;
        int playerbet2 = player->tableInfo.playerInfo[1].bet;
        int playerbet3 = player->tableInfo.playerInfo[2].bet;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
        ui ->line_player2->setText(QString::fromStdString(playerName2));
        ui ->line_player3->setText(QString::fromStdString(playerName3));
        ui->line_bet1->setText(QString::fromStdString(std::to_string(playerbet1)));
        ui->line_bet2->setText(QString::fromStdString(std::to_string(playerbet2)));
        ui->line_bet3->setText(QString::fromStdString(std::to_string(playerbet3)));
    }

    if (player->tableInfo.player_num<=4) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        std::string playerName2 = player->tableInfo.playerInfo[1].name;
        std::string playerName3 = player->tableInfo.playerInfo[2].name;
        std::string playerName4 = player->tableInfo.playerInfo[3].name;
        int playerbet1 = player->tableInfo.playerInfo[0].bet;
        int playerbet2 = player->tableInfo.playerInfo[1].bet;
        int playerbet3 = player->tableInfo.playerInfo[2].bet;
        int playerbet4 = player->tableInfo.playerInfo[3].bet;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
        ui ->line_player2->setText(QString::fromStdString(playerName2));
        ui ->line_player3->setText(QString::fromStdString(playerName3));
        ui ->line_player4->setText(QString::fromStdString(playerName4));
        ui->line_bet1->setText(QString::fromStdString(std::to_string(playerbet1)));
        ui->line_bet2->setText(QString::fromStdString(std::to_string(playerbet2)));
        ui->line_bet3->setText(QString::fromStdString(std::to_string(playerbet3)));
        ui->line_bet4->setText(QString::fromStdString(std::to_string(playerbet4)));
    }

    if (player->tableInfo.player_num<=5) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        std::string playerName2 = player->tableInfo.playerInfo[1].name;
        std::string playerName3 = player->tableInfo.playerInfo[2].name;
        std::string playerName4 = player->tableInfo.playerInfo[3].name;
        std::string playerName5 = player->tableInfo.playerInfo[4].name;
        int playerbet1 = player->tableInfo.playerInfo[0].bet;
        int playerbet2 = player->tableInfo.playerInfo[1].bet;
        int playerbet3 = player->tableInfo.playerInfo[2].bet;
        int playerbet4 = player->tableInfo.playerInfo[3].bet;
        int playerbet5 = player->tableInfo.playerInfo[4].bet;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
        ui ->line_player2->setText(QString::fromStdString(playerName2));
        ui ->line_player3->setText(QString::fromStdString(playerName3));
        ui ->line_player4->setText(QString::fromStdString(playerName4));
        ui ->line_player5->setText(QString::fromStdString(playerName5));
        ui->line_bet1->setText(QString::fromStdString(std::to_string(playerbet1)));
        ui->line_bet2->setText(QString::fromStdString(std::to_string(playerbet2)));
        ui->line_bet3->setText(QString::fromStdString(std::to_string(playerbet3)));
        ui->line_bet4->setText(QString::fromStdString(std::to_string(playerbet4)));
        ui->line_bet5->setText(QString::fromStdString(std::to_string(playerbet5)));
    }

    if (player->tableInfo.player_num<=6) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        std::string playerName2 = player->tableInfo.playerInfo[1].name;
        std::string playerName3 = player->tableInfo.playerInfo[2].name;
        std::string playerName4 = player->tableInfo.playerInfo[3].name;
        std::string playerName5 = player->tableInfo.playerInfo[4].name;
        std::string playerName6 = player->tableInfo.playerInfo[5].name;
        int playerbet1 = player->tableInfo.playerInfo[0].bet;
        int playerbet2 = player->tableInfo.playerInfo[1].bet;
        int playerbet3 = player->tableInfo.playerInfo[2].bet;
        int playerbet4 = player->tableInfo.playerInfo[3].bet;
        int playerbet5 = player->tableInfo.playerInfo[4].bet;
        int playerbet6 = player->tableInfo.playerInfo[5].bet;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
        ui ->line_player2->setText(QString::fromStdString(playerName2));
        ui ->line_player3->setText(QString::fromStdString(playerName3));
        ui ->line_player4->setText(QString::fromStdString(playerName4));
        ui ->line_player5->setText(QString::fromStdString(playerName5));
        ui ->line_player6->setText(QString::fromStdString(playerName6));
        ui->line_bet1->setText(QString::fromStdString(std::to_string(playerbet1)));
        ui->line_bet2->setText(QString::fromStdString(std::to_string(playerbet2)));
        ui->line_bet3->setText(QString::fromStdString(std::to_string(playerbet3)));
        ui->line_bet4->setText(QString::fromStdString(std::to_string(playerbet4)));
        ui->line_bet5->setText(QString::fromStdString(std::to_string(playerbet5)));
        ui->line_bet6->setText(QString::fromStdString(std::to_string(playerbet6)));
    }

    if (player->tableInfo.player_num<=7) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        std::string playerName2 = player->tableInfo.playerInfo[1].name;
        std::string playerName3 = player->tableInfo.playerInfo[2].name;
        std::string playerName4 = player->tableInfo.playerInfo[3].name;
        std::string playerName5 = player->tableInfo.playerInfo[4].name;
        std::string playerName6 = player->tableInfo.playerInfo[5].name;
        std::string playerName7 = player->tableInfo.playerInfo[6].name;
        int playerbet1 = player->tableInfo.playerInfo[0].bet;
        int playerbet2 = player->tableInfo.playerInfo[1].bet;
        int playerbet3 = player->tableInfo.playerInfo[2].bet;
        int playerbet4 = player->tableInfo.playerInfo[3].bet;
        int playerbet5 = player->tableInfo.playerInfo[4].bet;
        int playerbet6 = player->tableInfo.playerInfo[5].bet;
        int playerbet7 = player->tableInfo.playerInfo[6].bet;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
        ui ->line_player2->setText(QString::fromStdString(playerName2));
        ui ->line_player3->setText(QString::fromStdString(playerName3));
        ui ->line_player4->setText(QString::fromStdString(playerName4));
        ui ->line_player5->setText(QString::fromStdString(playerName5));
        ui ->line_player6->setText(QString::fromStdString(playerName6));
        ui ->line_player7->setText(QString::fromStdString(playerName7));
        ui->line_bet1->setText(QString::fromStdString(std::to_string(playerbet1)));
        ui->line_bet2->setText(QString::fromStdString(std::to_string(playerbet2)));
        ui->line_bet3->setText(QString::fromStdString(std::to_string(playerbet3)));
        ui->line_bet4->setText(QString::fromStdString(std::to_string(playerbet4)));
        ui->line_bet5->setText(QString::fromStdString(std::to_string(playerbet5)));
        ui->line_bet6->setText(QString::fromStdString(std::to_string(playerbet6)));
        ui->line_bet7->setText(QString::fromStdString(std::to_string(playerbet7)));
    }

    if (player->tableInfo.player_num<=7) {
        std::string playerName1 = player->tableInfo.playerInfo[0].name;
        std::string playerName2 = player->tableInfo.playerInfo[1].name;
        std::string playerName3 = player->tableInfo.playerInfo[2].name;
        std::string playerName4 = player->tableInfo.playerInfo[3].name;
        std::string playerName5 = player->tableInfo.playerInfo[4].name;
        std::string playerName6 = player->tableInfo.playerInfo[5].name;
        std::string playerName7 = player->tableInfo.playerInfo[6].name;
        std::string playerName8 = player->tableInfo.playerInfo[7].name;
        int playerbet1 = player->tableInfo.playerInfo[0].bet;
        int playerbet2 = player->tableInfo.playerInfo[1].bet;
        int playerbet3 = player->tableInfo.playerInfo[2].bet;
        int playerbet4 = player->tableInfo.playerInfo[3].bet;
        int playerbet5 = player->tableInfo.playerInfo[4].bet;
        int playerbet6 = player->tableInfo.playerInfo[5].bet;
        int playerbet7 = player->tableInfo.playerInfo[6].bet;
        int playerbet8 = player->tableInfo.playerInfo[7].bet;
        ui ->line_player1->setText(QString::fromStdString(playerName1));
        ui ->line_player2->setText(QString::fromStdString(playerName2));
        ui ->line_player3->setText(QString::fromStdString(playerName3));
        ui ->line_player4->setText(QString::fromStdString(playerName4));
        ui ->line_player5->setText(QString::fromStdString(playerName5));
        ui ->line_player6->setText(QString::fromStdString(playerName6));
        ui ->line_player7->setText(QString::fromStdString(playerName7));
        ui ->line_player8->setText(QString::fromStdString(playerName8));
        ui->line_bet1->setText(QString::fromStdString(std::to_string(playerbet1)));
        ui->line_bet2->setText(QString::fromStdString(std::to_string(playerbet2)));
        ui->line_bet3->setText(QString::fromStdString(std::to_string(playerbet3)));
        ui->line_bet4->setText(QString::fromStdString(std::to_string(playerbet4)));
        ui->line_bet5->setText(QString::fromStdString(std::to_string(playerbet5)));
        ui->line_bet6->setText(QString::fromStdString(std::to_string(playerbet6)));
        ui->line_bet7->setText(QString::fromStdString(std::to_string(playerbet7)));
        ui->line_bet8->setText(QString::fromStdString(std::to_string(playerbet7)));
    }




    // Update community cards (middle cards)
    update_community_cards();

}


void GameWindow::update_community_cards() {
    Table table;
    const std::vector<Card>& communityCards = table.communityCards;

    // Display the first three community cards initially
    for (int i = 0; i < 3; ++i) {
        update_middle_card_display(i + 1, communityCards[i]);
    }
}

void GameWindow::update_middle_card_display(int cardIndex, const Card& card) {
    QLabel* middleCardLabel = findChild<QLabel*>(QString("label_middlecard%1").arg(cardIndex));
    if (middleCardLabel) {
        // Get the image path for the card
        //QString imagePath = Get_image_path(card.suit, std::to_string(card.getValue()), false);
//many bugs but i will solve them
        // Loading and setting the image to the QLabel
        //QPixmap image(imagePath);
        //ui->middleCardLabel->setPixmap(image);
    }
}


void GameWindow::update_from_display(PokerPlayer* player){

}



// beginning of switch from name tag to bank display

void GameWindow::on_line_player1_cursorPositionChanged(PokerPlayer* player)
{
    QString text_line = ui->line_player1->text();
    std::string text = text_line.toStdString();

    std::string name = player->tableInfo.playerInfo[0].name;
    std::string stack =  std::to_string(player->tableInfo.playerInfo[0].stack_size);

    if (text == stack){
        QString name_qt = QString::fromStdString(name);
        ui->line_player1->setText(name_qt);
    }
    else {
        QString stack_qt = QString::fromStdString(stack);
        ui->line_player1->setText(stack_qt);
    }
}
void GameWindow::on_line_player2_cursorPositionChanged(PokerPlayer* player)
{
    if (player->tableInfo.player_num >= 2){
        QString text_line = ui->line_player2->text();
        std::string text = text_line.toStdString();

        std::string name = player->tableInfo.playerInfo[1].name;
        std::string stack =  std::to_string(player->tableInfo.playerInfo[1].stack_size);

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
void GameWindow::on_line_player3_cursorPositionChanged(PokerPlayer* player)
{
    if (player->tableInfo.player_num >= 3){
        QString text_line = ui->line_player3->text();
        std::string text = text_line.toStdString();

        std::string name = player->tableInfo.playerInfo[2].name;
        std::string stack =  std::to_string(player->tableInfo.playerInfo[2].stack_size);

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
void GameWindow::on_line_player4_cursorPositionChanged(PokerPlayer* player)
{
    if (player->tableInfo.player_num >= 4){
        QString text_line = ui->line_player4->text();
        std::string text = text_line.toStdString();

        std::string name = player->tableInfo.playerInfo[3].name;
        std::string stack =  std::to_string(player->tableInfo.playerInfo[3].stack_size);

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
void GameWindow::on_line_player5_cursorPositionChanged(PokerPlayer* player)
{
    if (player->tableInfo.player_num >= 5){
        QString text_line = ui->line_player5->text();
        std::string text = text_line.toStdString();

        std::string name = player->tableInfo.playerInfo[4].name;
        std::string stack =  std::to_string(player->tableInfo.playerInfo[4].stack_size);

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
void GameWindow::on_line_player6_cursorPositionChanged(PokerPlayer* player)
{
    if (player->tableInfo.player_num >= 6){
        QString text_line = ui->line_player6->text();
        std::string text = text_line.toStdString();

        std::string name = player->tableInfo.playerInfo[5].name;
        std::string stack =  std::to_string(player->tableInfo.playerInfo[5].stack_size);

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
void GameWindow::on_line_player7_cursorPositionChanged(PokerPlayer* player)
{
    if (player->tableInfo.player_num >= 7){
        QString text_line = ui->line_player7->text();
        std::string text = text_line.toStdString();

        std::string name = player->tableInfo.playerInfo[6].name;
        std::string stack =  std::to_string(player->tableInfo.playerInfo[6].stack_size);

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
void GameWindow::on_line_player8_cursorPositionChanged(PokerPlayer* player)
{
    if (player->tableInfo.player_num == 8){
        QString text_line = ui->line_player8->text();
        std::string text = text_line.toStdString();

        std::string name = player->tableInfo.playerInfo[7].name;
        std::string stack =  std::to_string(player->tableInfo.playerInfo[7].stack_size);

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

// beginning of initial display of names and bet






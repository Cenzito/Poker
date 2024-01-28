#include "gamelocalwindow.hpp"
#include "ui_gamewindow.h"
#include <qdebug.h>
#include <QApplication>
#include <sstream>

GameLocalWindow::GameLocalWindow(QWidget *parent, std::string p) : GameWindow(parent, p), game(8)
{
    //make player join the game
    //qDebug() << QString::fromStdString(game_player.getName());


    QObject::connect(this, &GameLocalWindow::addBot, &game, &GameLocal::addBot);
    QObject::connect(this, &GameLocalWindow::removePlayer, &game, &GameLocal::RemovePlayer);

    game.JoinGame(&game_player);

}



void GameLocalWindow::onAddBotClicked(){
    int level =  ui->AddBot->currentIndex();
    qDebug() << level;
    emit addBot(level);
};

void GameLocalWindow::onKickButtonClicked(int num) {
    QLineEdit* line_player = findChild<QLineEdit*>(QString("line_player%1").arg(num));
    std::string name = line_player->text().toStdString();

    std::istringstream iss(name);
    std::vector<std::string> wordsArray(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    emit removePlayer(wordsArray[0]);
}

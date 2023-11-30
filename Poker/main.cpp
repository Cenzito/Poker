#include "./GameLogic/PokerPlayer.hpp"

#include "./Visuals/MainWindow/mainwindow.hpp"

#include <QApplication>


int main(int argc, char *argv[]) {
    Game pokerGame(4);
    pokerGame.startGame();

    return 0;
    
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
}

//#include "./logic/headers/PokerPlayer.hpp"

#include "./Visuals/MainWindow/mainwindow.hpp"
#include "./GameLogic/Game.hpp"
#include <QApplication>


int main(int argc, char *argv[]) {
    Game pokerGame(4);
    pokerGame.startGame();

    
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
}

//test


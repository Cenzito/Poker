

#include "./Visuals/MainWindow/mainwindow.hpp"
#include "./Visuals/Gamewindow/gamewindow.hpp"

#include "./Visuals/Gamewindow/gamelocalwindow.hpp"
#include "./GameLogic/Card.cpp"
#include "./GameLogic/Deck.cpp"
#include "./GameLogic/PokerHand.cpp"
#include "./GameLogic/GameLocal.hpp"
#include "./Bots/Hard/Cenzo/BotCenzo.hpp"

#include <QApplication>


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    GameLocalWindow w;
    BotCenzo bot1 = BotCenzo("bot1");
    BotCenzo bot2 = BotCenzo("bot2");
    BotCenzo bot3 = BotCenzo("bot3");
    w.game.addBot(&bot1);
    w.game.addBot(&bot2);
    w.game.addBot(&bot3);
    //w.show();

    w.game.nextHand();

    return a.exec();



/*
    //QApplication a(argc, argv);
    GameLocal w(2);
    BotCenzo bot1 = BotCenzo("bot1", 7);
    BotCenzo bot2 = BotCenzo("bot2", 7);
    //BotCenzo bot3 = BotCenzo("bot1", 7);
    //BotCenzo bot4 = BotCenzo("bot2", 7);
    //BotCenzo bot5 = BotCenzo("bot1", 7);
    w.addBot(&bot1);
    w.addBot(&bot2);
    //w.addBot(&bot3);
    //w.addBot(&bot4);
    //w.addBot(&bot5);
    //w.show();
    w.nextHand();

    return 1;

*/

}

//test


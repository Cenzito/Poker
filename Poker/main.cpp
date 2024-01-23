

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
    Bot bot1 = Bot("bot1", 0);
    Bot bot2 = Bot("bot2", 0);
    w.game.addBot(&bot1);
    w.game.addBot(&bot2);
    w.show();


    w.game.nextHand();

    return a.exec();


    //Bot bot1 = Bot("bot1", 0);
    //Bot bot2 = Bot("bot2", 0);
    Bot bot3 = Bot("bot3", 0);

    GameLocal game(5);

    game.addBot(&bot1);
    game.addBot(&bot2);
    game.addBot(&bot3);


/*
    //QApplication a(argc, argv);

    GameLocal w(2);
    BotCenzo bot1 = BotCenzo("bot1", 7);
    BotCenzo bot2 = BotCenzo("bot2", 7);
    w.addBot(&bot1);
    w.addBot(&bot2);
    //w.show();
    w.nextHand();

    return 1;

*/

}

//test


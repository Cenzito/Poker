

#include "./Visuals/MainWindow/mainwindow.hpp"
#include "./Visuals/Gamewindow/gamewindow.hpp"


#include "./Visuals/Gamewindow/gamelocalwindow.hpp"
#include "./GameLogic/Card.cpp"
#include "./GameLogic/Deck.cpp"
#include "./GameLogic/PokerHand.cpp"
#include "./GameLogic/GameLocal.hpp"

#include <QApplication>


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    GameLocalWindow w;
    BotDarius bot1 = BotDarius("Alpha");
    Bot bot2 = Bot("bot2",0);

    //Bot bot1 = Bot("bot1", 0);
    //Bot bot2 = Bot("bot2", 0);
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


    return 1;


}

//test


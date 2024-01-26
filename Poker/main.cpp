
#include "./Visuals/MainWindow/mainwindow.hpp"
#include "./Visuals/Gamewindow/gamewindow.hpp"


#include "./Visuals/Gamewindow/gamelocalwindow.hpp"
#include "./GameLogic/Card.cpp"
#include "./GameLogic/Deck.cpp"
#include "./GameLogic/PokerHand.cpp"
#include "./GameLogic/GameLocal.hpp"
#include "./Bots/Hard/Cenzo/BotCenzo.hpp"
#include "./Bots/Easy/MonkeyBot.hpp"

#include <QApplication>


int main(int argc, char *argv[]) {

    qDebug() << "Hello";


    QApplication a(argc, argv);

    GameLocalWindow w;

    BotDarius bot1 = BotDarius("Alpha");
    //Bot bot1 = Bot("bot2",0);
    MonkeyBot bot2 = MonkeyBot("Beta");

    //Bot bot1 = Bot("bot1", 0);
    //Bot bot2 = Bot("bot2", 0);

    w.game.addBot(&bot1);
    w.game.addBot(&bot2);
    w.show();

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



    //w.show();
    //w.game_player.hand.push_back(Card(Suit::Spades, 4));
    //w.game_player.hand.push_back(Card(Suit::Hearts, 12));
    //w.game_player.tableInfo.playerInfo[0] = PlayerInfo("Remi", 1000, 0);
    //w.game_player.tableInfo.player_num = 1;
    // w.update_display();

/*
    if( hand.has_royal_flush() == true ) std::cout << "Royal flush";
    else std::cout << "Not royal flush";
    //if( hand.is_member(card1)==true) std::cout << "Card is in hand";
    //else std::cout << "Card is not in hand"<<std::endl;
    if(hand.has_flush()==true) std::cout << " Flush"<<std::endl;
    else std::cout << "Not Flush"<<std::endl;
    if(hand.has_straight()==true) std::cout << " Straight"<<std::endl;
    else std::cout << "Not Straight"<<std::endl;

    hand.order_cards();
    for (int i = 0; i < hand.get_cards().size(); i++) {
        std::cout << hand.get_cards()[i] << " ";
    }
    if(hand.has_straight_flush()==true) std::cout << " Straight flush"<<std::endl;
    else std::cout << "Not Straight flush"<<std::endl;


    if(hand.has_four_of_a_kind()==true) std::cout << " Four of a kind"<<std::endl;
    else std::cout << "Not Four of a kind"<<std::endl;
    if(hand.has_full_house()==true) std::cout << " Full house"<<std::endl;
    else std::cout << "Not Full house"<<std::endl;
    if(hand.has_three_of_a_kind()==true) std::cout << " Three of a kind"<<std::endl;
    else std::cout << "Not Three of a kind"<<std::endl;
    if(hand.has_two_pairs()==true) std::cout << " Two pairs"<<std::endl;
    else std::cout << "Not Two pairs"<<std::endl;
    if(hand.has_pair()==true) std::cout << " Pair"<<std::endl;
    else std::cout << "Not Pair"<<std::endl;
    std::vector<int> score,score1,score2;
    score=hand.get_score();
    for (int i = 0; i < score.size(); i++) {
        std::cout << score[i] << " ";
    }
    std::cout << std::endl;
    std::cout <<score.size()<< std::endl;
    std::cout<<std::endl;
    hand1.order_cards();
    for (int i = 0; i < hand1.get_cards().size(); i++) {
        std::cout << hand1.get_cards()[i] << " ";
    }
    std::cout<<std::endl;
    hand2.order_cards();
    for (int i = 0; i < hand2.get_cards().size(); i++) {
        std::cout << hand2.get_cards()[i] << " ";
    }
    std::cout<<std::endl;
    score1=hand1.get_score();
    for (int i = 0; i < score1.size(); i++) {
        std::cout << score1[i] << " ";
    }
    std::cout<<std::endl;
    score2=hand2.get_score();
    for (int i = 0; i < score2.size(); i++) {
        std::cout << score2[i] << " ";
    }
    std::cout<<std::endl;
    std::cout << compare_hands(hand1, hand2) << std::endl;
    return 0;

*/

}

//test

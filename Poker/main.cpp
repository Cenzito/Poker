//#include "./logic/headers/PokerPlayer.hpp"

// #include "./Visuals/MainWindow/mainwindow.hpp"
#include "./GameLogic/Game.hpp"
#include "./GameLogic/Card.cpp"
#include "./GameLogic/Deck.cpp"
#include "./GameLogic/PokerHand.hpp"

//#include <QApplication>


int main(int argc, char *argv[]) {
    //Game pokerGame(4);
    //pokerGame.startGame();
    std::cout << "Hello World!" << std::endl;
    Card card1(Suit::Spades, 1);
    Card card2(Suit::Spades, 2);
    Card card3(Suit::Hearts, 2);
    //std::cout << card1 << std::endl;
    //std::cout << card2 << std::endl;
    //std::cout << (card1 < card2) << std::endl;
    //std::cout << (card2 < card3) << std::endl;
    //std::cout << (card1 < card3) << std::endl;
    Deck deck;
    deck.shuffleDeck();
    std::cout << deck.dealCard() << std::endl;
    std::cout << deck.dealCard() << std::endl;
    std::cout << deck.dealCard() << std::endl;
    //std:: vector <Card> cards= {Card(Suit::Spades, 10), Card(Suit::Spades,11), Card(Suit::Spades,12), Card(Suit::Spades,13), Card(Suit::Spades,14)};
    //std::cout<< cards[0];
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
    PokerHand hand ({Card(Suit::Spades, 10), Card(Suit::Spades,11), Card(Suit::Spades,12), Card(Suit::Spades,13), Card(Suit::Spades,14)});
    //std:: cout<< hand.is_royal_flush();
    return 0;
}
//testing

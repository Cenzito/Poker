

#include "./Visuals/MainWindow/mainwindow.hpp"
#include "./GameLogic/Game.hpp"
#include "./GameLogic/Card.cpp"
#include "./GameLogic/Deck.cpp"
#include "./GameLogic/PokerHand.cpp"

#include <QApplication>


int main(int argc, char *argv[]) {
    Game pokerGame(4);
    pokerGame.startGame();
    std::cout << "Hello World!" << std::endl;
    Card card1(Suit::Spades, 1);
    Card card2(Suit::Spades, 2);
    Card card3(Suit::Hearts, 2);
    std::cout << card1 << std::endl;
    std::cout << card2 << std::endl;
    std::cout << (card1 < card2) << std::endl;
    std::cout << (card2 < card3) << std::endl;
    std::cout << (card1 < card3) << std::endl;
    Deck deck;
    deck.shuffleDeck();
    PokerHand hand ({Card(Suit::Spades, 9), Card(Suit::Spades,11), Card(Suit::Spades,12), Card(Suit::Spades,13), Card(Suit::Spades,14)});
    std::cout << hand.get_cards()[0];
    if( hand.is_royal_flush() == true ) std::cout << "Royal flush";
    else std::cout << "Not royal flush";

    return 0;
}

//test


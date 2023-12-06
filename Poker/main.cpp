

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
    PokerHand hand ({Card(Suit::Spades, 2), Card(Suit::Clubs,4), Card(Suit::Spades, 3), Card(Suit::Spades, 5), Card(Suit::Spades,13), Card(Suit::Hearts,6) });
    //PokerHand hand ({});
    std::cout << hand.get_cards()[0];

    if( hand.is_royal_flush() == true ) std::cout << "Royal flush";
    else std::cout << "Not royal flush";
    if( hand.is_member(card1)==true) std::cout << "Card is in hand";
    else std::cout << "Card is not in hand"<<std::endl;
    if(hand.is_flush()==true) std::cout << " Flush"<<std::endl;
    else std::cout << "Not Flush"<<std::endl;
    if(hand.is_straight()==true) std::cout << " Straight"<<std::endl;
    else std::cout << "Not Straight"<<std::endl;
    hand.order_cards();
    for (int i = 0; i < hand.get_cards().size(); i++) {
        std::cout << hand.get_cards()[i] << " ";
    }
    return 0;

}

//test


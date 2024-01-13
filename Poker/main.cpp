

#include "./Visuals/MainWindow/mainwindow.hpp"
#include "./Visuals/Gamewindow/gamewindow.hpp"

#include "./GameLogic/Card.cpp"
#include "./GameLogic/Deck.cpp"
#include "./GameLogic/PokerHand.cpp"

#include <QApplication>


int main(int argc, char *argv[]) {


    //Game pokerGame(4);
    //pokerGame.startGame();

    //commented these 4 because of conflicts (delete and recreate pull request if this is unneccesary)
    QApplication a(argc, argv);
    GameWindow w;

    w.show();
    w.game_player.hand.push_back(Card(Suit::Spades, 4));
    w.game_player.hand.push_back(Card(Suit::Hearts, 12));
    w.update_display();

    return a.exec();

  
    std::cout << "Hello World!" << std::endl;
    //Card card1(Suit::Spades, 1);
    //Card card2(Suit::Spades, 2);
    //Card card3(Suit::Hearts, 2);
    //std::cout << card1 << std::endl;
    //std::cout << card2 << std::endl;
    //std::cout << (card1 < card2) << std::endl;
    //std::cout << (card2 < card3) << std::endl;
    //std::cout << (card1 < card3) << std::endl;
    Deck deck;
    deck.shuffleDeck();
    PokerHand hand1({deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard()}); //7 random cards
    PokerHand hand2({deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard(), deck.dealCard()}); //another 7 random cards
    PokerHand hand ({Card(Suit::Clubs, 12), Card(Suit::Clubs,11), Card(Suit::Clubs, 8), Card(Suit::Clubs, 7), Card(Suit::Spades,4), Card(Suit::Clubs,4), Card(Suit::Diamonds, 4)});
    std::cout << hand.get_cards()[0];

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


}

//test


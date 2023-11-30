#include "Game.hpp"
#include <iostream>



Game::Game(int numOfPlayers) {
    for (int i = 0; i < numOfPlayers; ++i) {
        players.emplace_back("Player " + std::to_string(i + 1), 1000); //1000 cest les chips
    }
}

void Game::startGame() {
    deck.shuffleDeck();

    // deal two random cards
    for (PokerPlayer& player : players) {
        std::vector<Card> hand = {deck.dealCard(), deck.dealCard()};
        player.receiveCards(hand);
        std::cout << player.getName() << "'s hand: ";
        player.showHand();
    }


    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;

    // Flop
    std::cout << "Flop: ";
    for (int i = 0; i < 3; ++i) {
        Card card = deck.dealCard();
        communityCards.push_back(card);
        std::cout << card.toString() << " ";
    }
    std::cout << std::endl;


    // bet
    //for (PokerPlayer& player : players) {
    //    player.action();
    //}


    // burn and card
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "Turn: ";
    Card turnCard = deck.dealCard();
    communityCards.push_back(turnCard);
    std::cout << turnCard.toString() << std::endl;

    // bet

    // river
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "River: ";
    Card riverCard = deck.dealCard();
    communityCards.push_back(riverCard);
    std::cout << riverCard.toString() << std::endl;

    //betting
}

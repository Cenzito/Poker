#include "Game.hpp"
#include <iostream>



Game::Game(int numOfPlayers) {
    //This will need to be changed
    //Create a Game where people will join
    for (int i = 0; i < numOfPlayers; ++i) {
        players.emplace_back("Player " + std::to_string(i + 1), 1000); //1000 cest les chips
    }
}


void Game::JoinGame(PokerPlayer player) {
    //player joins game so we add him to the table
    //in future we will not just give money but search for the account of the player and add that much money
    //or do other stuff
    PlayerInfo playerinfo = PlayerInfo(player.getName(), 1000, 0);
    //would need to do a try in case of error if room is full
    tableInfo.JoinTable(playerinfo);
}

//update the table information of every player in the game
//every time we have a change we will call that
//ui will need to be changed in each players
void Game::update() {
    for (PokerPlayer& player : players) {
        player.updateTable(tableInfo);
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
        tableInfo.addCard(card);
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
    tableInfo.addCard(turnCard);
    std::cout << turnCard.toString() << std::endl;

    // bet

    // river
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "River: ";
    Card riverCard = deck.dealCard();
    tableInfo.addCard(riverCard);
    std::cout << riverCard.toString() << std::endl;

    //betting
}

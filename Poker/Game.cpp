#include "Game.hpp"
#include <iostream>



Game::Game(int numOfPlayers) {
    //This will need to be changed
    //Create a Game where people will join
    for (int i = 0; i < numOfPlayers; ++i) {
        players.emplace_back("Player " + std::to_string(i + 1), 1000); //1000 cest les chips
    }
}

int Game::getFreeSeat() {
    Table &t = tableInfo;
    for (int i = 0; i<t.seats; i++) {
        if (!(t.playerInfo.find(i) == t.playerInfo.end())) {
            return i;
        }
    }
    return -1;
}

void Game::JoinGame(PokerPlayer player) {

    //player joins game so we add him to the table
    //in future we will not just give money but search for the account of the player and add that much money
    //or do other stuff
    PlayerInfo playerinfo = PlayerInfo(player.getName(), 1000, 0);

    getFreeSeat();
    //would need to do a try in case of error if room is full
    if (tableInfo.player_num >= tableInfo.seats)  {
        return;
    } else {
        tableInfo.playerInfo.insert({getFreeSeat(), playerinfo});
        players.push_back(player);
    }
}


void Game::addBot(PokerPlayer bot) {
    Game::JoinGame(bot);
}


//to implement
void Game::nextHand(){
    for (PokerPlayer& player : players) {
        player.removeCards();
    }


    tableInfo.pot=0;
    tableInfo.smallBlindPlayer += 1;
    tableInfo.communityCards=std::vector<Card>();
}

//to implement
void Game::addBet(int pos, int amount){
    tableInfo.playerInfo.at(pos).stack_size -= amount;
    tableInfo.pot += amount;
}

//to implement
void Game::winMoney(int pos, int amount){
    tableInfo.playerInfo.at(pos).stack_size += amount;
}




void Game::addCard(Card card) {tableInfo.communityCards.push_back(card);}








//update the table information of every player in the game
//every time we have a change we will call that
//ui will need to be changed in each players
void Game::update() {
    for (PokerPlayer& player : players) {
        player.updateTable(tableInfo);
    }
}


void Game::startRound() {
    deck.shuffleDeck();

    // deal two random cards
    for (PokerPlayer& player : players) {
        std::vector<Card> hand = {deck.dealCard(), deck.dealCard()};
        player.receiveCards(hand);
        std::cout << player.getName() << "'s hand: ";
        player.getHand();
    }


    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;

    // Flop
    std::cout << "Flop: ";
    for (int i = 0; i < 3; ++i) {
        Card card = deck.dealCard();
        addCard(card);
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
    addCard(turnCard);
    std::cout << turnCard.toString() << std::endl;

    // bet

    // river
    std::cout << "Burn: " << deck.dealCard().toString() << std::endl;
    std::cout << "River: ";
    Card riverCard = deck.dealCard();
    addCard(riverCard);
    std::cout << riverCard.toString() << std::endl;

    //betting
}

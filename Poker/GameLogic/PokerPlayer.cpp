#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>


PokerPlayer::PokerPlayer(const std::string& name, int initialChips) : name(name), chips(initialChips) {}

int PokerPlayer::getChips() const {
    return chips;
}

void PokerPlayer::placeBet(int amount) {
    if (amount <= chips) {
        chips -= amount;
        std::cout << name << " bets " << amount << " chips." << std::endl;
    } else {
        std::cout << name << " cannot bet that amount." << std::endl;
    }
}

void PokerPlayer::receiveCards(const std::vector<Card>& cards) {
    hand = cards;
}


void PokerPlayer::showHand() const {
    std::cout << name << "'s hand: ";
    for (const auto& card : hand) {
        std::cout << card << " ";
    }
    std::cout << std::endl;
}

void PokerPlayer::winChips(int amount) {
    chips += amount;
    std::cout << name << " wins " << amount << " chips." << std::endl;
}

<<<<<<< Updated upstream
void PokerPlayer::action(std::vector<int> table, int minAmount, int type) {
    std::cout << "Pot: " << table[0] << std::endl;
    for (int i = 1; i < table.size();i++) {
        std::cout << "Bet" << table[i] << std::endl;
    }
};
=======
void PokerPlayer::action(std::vector<int> table, int minAmount, int type){
    std::cout << "Total Pot" << std::endl;
};

>>>>>>> Stashed changes

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.toString();
    return os;
}


Card::Card(const std::string& suit, int value) : suit(suit), value(value) {}

std::string Card::getSuit() const {
    return suit;
}

int Card::getValue() const {
    return value;
}

std::string Card::toString() const {
    return std::to_string(value) + suit;
}


Deck::Deck() : currentCardIndex(0) {
    std::string suits[4] = {"H", "D", "C", "S"};
    for (const std::string& suit : suits) {
        for (int value = 1; value <= 13; ++value) {
            cards.emplace_back(suit, value);
        }
    }
    shuffleDeck();
}



void Deck::shuffleDeck() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();


    std::mt19937 engine(seed);
    std::shuffle(cards.begin(), cards.end(), engine);
    currentCardIndex = 0;
}


Card Deck::dealCard() {
    if (currentCardIndex < cards.size()) {
        return cards[currentCardIndex++];
    } else {
        throw std::out_of_range("No more cards in the deck");
    }
}

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
    for (PokerPlayer& player : players) {
        player.action();
    }


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
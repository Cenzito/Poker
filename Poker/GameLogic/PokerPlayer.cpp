#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>


PokerPlayer::PokerPlayer(const std::string& name) : name(name) {}


int PokerPlayer::decideBet(int currentHighestBet, int money, int minimumRaise) {
    // Implement player decision logic here
    // For now, returning a basic decision
    return currentHighestBet + minimumRaise;
}

void PokerPlayer::receiveCards(const std::vector<Card>& newHand) {
    hand = newHand;
}

void PokerPlayer::updateTable(const Table table) {
    tableInfo = table;
}

const std::string& PokerPlayer::getName() const {
    return name;
}


std::vector<Card> PokerPlayer::getHand() const {
    std::cout << name << "'s hand: ";
    for (const auto& card : hand) {
        std::cout << card << " ";
    }
    std::cout << std::endl;
    return hand;
}


void PokerPlayer::removeCards() {
    hand = std::vector<Card>();
}

/*
void PokerPlayer::action(std::vector<int> table, int minAmount, int type) {
    std::cout << "Pot: " << table[0] << std::endl;
    for (int i = 1; i < table.size();i++) {
        std::cout << "Bet" << table[i] << std::endl;
    }
};*/

void PokerPlayer::call(int bet_on_table) {
    //tell server you want to call
}

void PokerPlayer::raise(int bet_on_table) { //TO BE DONE
    //: Ask raise amount !!!there are minimums (check poker rules) TO DO THE MINIMUMS IF statements
    std::string userInput;
    std::cout << "By how much woud you like to raise: ";
    std::cin >> userInput;
    int amount_to_raise = std::stoi(userInput); //stoi = string to integer

    //tell server how much you want to raise
}

void PokerPlayer::fold() {
    //tell server you want to fold
}



void PokerPlayer::updateChips() {
    //call server to update how many chips we have
}

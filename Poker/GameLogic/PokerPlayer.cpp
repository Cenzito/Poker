#include "PokerPlayer.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <iterator>


PokerPlayer::PokerPlayer(const std::string& name, int chips) : name(name), chips(chips), active(true) {}

bool PokerPlayer::isActive() const {
    return active;
}

bool PokerPlayer::canBet(int amount) const {
    return amount <= chips;
}

void PokerPlayer::bet(int amount) {
    chips -= amount;
    // Additional logic for betting (e.g., adding to the pot)
}

int PokerPlayer::decideBet(int currentHighestBet, int minimumRaise) {
    // Implement player decision logic here
    // For now, returning a basic decision
    return currentHighestBet + minimumRaise;
}

void PokerPlayer::receiveCards(const std::vector<Card>& newHand) {
    hand = newHand;
}

void PokerPlayer::updateTable(const Table& tableInfo) {
    currentTable = tableInfo;
}

const std::string& PokerPlayer::getName() const {
    return name;
}

//
void PokerPlayer::placeBet(int amount) {
    return;
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

void PokerPlayer::call(int bet_on_table) {//TO BE DONE: manage the case where Not enough chips DO THIS IN OTHER Function
    //decreases Chips available by bet_on_table - current_bet
    chips -= (bet_on_table - current_bet);
    //changes current_bet = bet_on_table
    current_bet = bet_on_table;
}

int PokerPlayer::raise(int bet_on_table) { //TO BE DONE
    //: Ask raise amount !!!there are minimums (check poker rules) TO DO THE MINIMUMS IF statements
    std::string userInput;
    std::cout << "By how much woud you like to raise: ";
    std::cin >> userInput;
    int amount_to_raise = std::stoi(userInput); //stoi = string to integer
    //CHECK IF amount_to_raise + current bet > bet on table + big blind or something
    //minimum based on small_blind and bet_on_table
    chips -= amount_to_raise; //decreases Chips available by amount_to_raise
    current_bet += amount_to_raise; //changes current_bet = amount_to_raise + current_bet
    //returns current_bet + amount_to_raise = updated current bet
    return current_bet; //this returns allows us to redefine the general bet on the table to ask other players to follow
}

int PokerPlayer::fold() {
    //change value of player_stopped_playing to true
    isFold = true;
    //returns current bet to add to total pot
    int current_bet_2 = current_bet; //allows us to make current bet 0 while returning current_bet_2
    current_bet = 0;
    return current_bet_2;
}


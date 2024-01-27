#include "MediumLeal.hpp"
#include <cmath>
#include <algorithm>
#include <random>
#include <qdebug.h>

float gen_rand_num() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

/*
Apart from already having a combination, there are different ways to check that a card combo is good
For instance:
- do we have consecutive ranks?
- are our cards close in rank and high?
so to make the bot more accurate, especially for the betting-rounds where the community cards are not all revealed.
*/

//functions just for the hand
bool MediumLeal::SameRank(std::vector<Card> hand) {
    if (hand[0].getValue() == hand[1].getValue()) {
        return true;
    }
    else {
        return false;
    }
}

bool MediumLeal::CloseRank(std::vector<Card> hand) { //+/- 2
    if (std::abs(hand[0].getValue() - hand[1].getValue())) {
        return true;
    }
    else {
        return false;
    }
}

bool MediumLeal::SameSuit(std::vector<Card> hand) {
    if (hand[0].getSuit() == hand[1].getSuit()) {
        return true;
    }
    else {
        return false;
    }
}

void MediumLeal::Action() {
    //now we will have to create cases for the betting rounds

    if (tableInfo.communityCards.size() == 0) {
        if (SameRank(hand) || SameSuit(hand) || CloseRank(hand)) {
            call_bet();
        }

        else {
            fold_bet();
        }

    }
    else if (tableInfo.communityCards.size() >= 3) {
        std::vector<Card> bot_hand = hand;
        for (int i = 0; i < tableInfo.communityCards.size(); i++) {
            bot_hand.emplace_back(tableInfo.communityCards[i]);
        }

        PokerHand educatedHand(bot_hand);

        NumericalCardValue = static_cast<int>(educatedHand.get_combination());

        float probability = 1 -  exp(-lambda * (static_cast<float>(NumericalCardValue) / 10));
        float rand_num = gen_rand_num();

        if (probability >= rand_num) {
            fold_bet();
        }

        else if (NumericalCardValue <= threshold) {
            call_bet();
        }

        else {
            raise_bet(tableInfo.current_biggest_bet); //raise by minimum raise amount

        }
    }

}

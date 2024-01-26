#include "MediumLeal.hpp"
#include <cmath>
#include <algorithm>
#include <random>


double randnum_generator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

int MediumLeal::CalcCardValue() { //make sure this happens every time the bot is given a new hand

    PokerHand educatedHand(hand);
    CardValue = educatedHand.get_combination();
    NumericalCardValue = static_cast<int>(CardValue);
}



/*void MediumLeal::Action() { //syntax changes as soon as we can make it an inhereted class
    float Probability = lambda * exp(-lambda * NumericalCardValue);
    float threshold = randnum_generator();


    //check i the generated threshold is greater than or equal to the calculated probability
    if (Probability >= threshold) {
        fold_bet();
    }
    else {
        //now we decide if to raise or call
        if (cardValue < card_threshold) {
            call_bet();
        }
        else {
            raise_bet(1);
        }
    }

}*/

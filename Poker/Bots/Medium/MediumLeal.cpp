#include "MediumLeal.hpp"
#include <cmath>
#include <algorithm>
#include <random>


float gen_rand_num() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen);
}

int MediumLeal::CalcCardValue() {
    PokerHand educatedHand(hand);
    CardValue = educatedHand.get_combination();
    NumericalCardValue = static_cast<int>(CardValue);
}


void MediumLeal::Action() { //syntax changes as soon as we can make it an inhereted class
    float probability = 1 - lambda * exp(-lambda * (NumericalCardValue / 10));
    float rand_num = gen_rand_num();

    if (probability >= rand_num) {
        fold_bet();
    }

    else if (NumericalCardValue <= threshold) {
        call_bet();
    }

    else {
        raise_bet(1);
    }
}

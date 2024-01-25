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

void MediumLeal::Action() { //syntax changes as soon as we can make it an inhereted class
    PokerHand educatedHand(hand); //where can we find cards?? --> make this make sense
    NumericalCardValue = static_cast<int>(educatedHand.get_combination());

    float probability = 1 - lambda * exp(-lambda * (NumericalCardValue / 10));
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

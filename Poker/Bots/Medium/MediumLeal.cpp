#include "MediumLeal.hpp"
#include <cmath>
#include <algorithm>


int MediumLeal::CalcCardValue() {

    PokerHand educatedHand(hand);
    CardValue = educatedHand.get_combination();
    NumericalCardValue = static_cast<int>(CardValue);
}

bool MediumLeal::ShouldFold() {

    if (chips < tableInfo.bet_on_table) {
       return true;
     }

    float Probability = exp(-lambda * NumericalCardValue);
    double threshold = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (threshold <= Probability) {
        return true;
    }
    else {
        return false;
    }
}


bool MediumLeal::ShouldRaise(int threshold) {
    if (NumericalCardValue < threshold) {
        return false;
     }
       else {
        return true;
    }

}

void MediumLeal::action() { //syntax changes as soon as we can make it an inhereted class

    if (ShouldFold() == false && ShouldRaise(threshold) == false) {
        call(tableInfo.bet_on_table);
    }
    if (ShouldFold() == false && ShouldRaise(threshold) == true) {
        //raise by 2 x small blind
        if (chips > 2*tableInfo.bet_on_table) {
            raise(2*tableInfo.bet_on_table);

        }

        else {
            call(tableInfo.bet_on_table);

        }


    }
    if (ShouldFold() == true) {
        fold();
    }
}

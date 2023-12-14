#include "MediumLeal.hpp"
#include <cmath>
#include <algorithm>


int MediumLeal::CalcCardValue() {

    PokerHand educatedHand(hand);
    CardValue = educatedHand.get_combination();
    NumericalCardValue = static_cast<int>(CardValue);
}

bool MediumLeal::ShouldFold() {

    if (chips < tableInfo.SBValue) {
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
        call(1);
    }
    if (ShouldFold() == false && ShouldRaise(threshold) == true) {
        //raise by 2 x small blind

    }
    if (ShouldFold() == true) {
        fold();
    }
}

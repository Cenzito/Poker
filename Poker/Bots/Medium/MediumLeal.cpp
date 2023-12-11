#include "MediumLeal.hpp"
#include <cmath>
#include <algorithm>


MediumLeal::MediumLeal() {
    //constructor
}

int MediumLeal::calcCardValue() {
    //calculate card value
    //can use the function in PokerHand
    /*
    if (is_pair() == true) {
        cardValue = ...;
    }
    ...
    */
}

bool MediumLeal::shouldFold() {
    //calculate probability according to outline
    /*
    double probability = pow(e, -4.7*(cardValue/10))

     */
}


bool MediumLeal::shouldRaise(int threshold) {

}

void MediumLeal::action(int MinValue, int type) { //syntax changes as soon as we can make it an inhereted class

}

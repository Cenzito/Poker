#include "MediumLeal.hpp"
#include <cmath>
#include <algorithm>


MediumLeal::MediumLeal() {
    //constructor
}

int MediumLeal::calcCardValue() {
    //calculate card value
    //branches -> community cards complete or not
    //check all of the is_smth
    /*cardValue = get_combination() */

}

bool MediumLeal::shouldFold() {

    /*if (our money less than call amount) {
       return true;
     } */

    //proba = e**(-lamda * cardValue)
    //threshold = randomvalue[0,1]
    /*if (threshhold <= proba) {
        return true;
    }
    else {
        return false;
    }*/

}


bool MediumLeal::shouldRaise(int threshold) {
    /* if (cardValue < threshold) {
     *  return false
     }
       else {
        return true;
    }
    */

}

void MediumLeal::action() { //syntax changes as soon as we can make it an inhereted class
    /*
    if (shouldFold is False && shouldRaise is False) {
        call
    }
    if (shouldFold is False && shouldRaise is True) {
        raise by 2xsmall bild
        if not enough money, call
    }
    if (shouldFold is True) {
        fold
    }

    */
}

#ifndef MEDIUMLEAL_HPP
#define MEDIUMLEAL_HPP
#include "../Bot.hpp"

class MediumLeal /*: public Bot*/ {
public:
    //constrcutor
    MediumLeal();

    //action
    void action() /*override*/;

private:
    int calcCardValue();
    bool shouldFold();
    bool shouldRaise(int threshhold);

};

#endif // MEDIUMLEAL_HPP


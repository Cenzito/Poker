#ifndef MEDIUMLEAL_HPP
#define MEDIUMLEAL_HPP
#include "../Bot.hpp"

class MediumLeal /*: public Bot*/ {
public:
    //constrcutor
    MediumLeal();

    //action
    void action(int MinAmount, int type) /*override*/;

private:
    double gamma;
    int calcCardValue();
    bool shouldFold();
    bool shouldRaise(int threshhold);

};

#endif // MEDIUMLEAL_HPP


#ifndef MEDIUMLEAL_HPP
#define MEDIUMLEAL_HPP
#include "../Bot.hpp"

class MediumLeal : public Bot {
public:
    //constrcutor
    MediumLeal();

    //action
    virtual void action(int MinAmount, int type);

private:
    double gamma;
    double proba;
    int calcCardValue();
    bool shouldFold();
    bool shouldRaise(int threshhold);

};

#endif // MEDIUMLEAL_HPP


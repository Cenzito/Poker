#ifndef BOTCENZO_H
#define BOTCENZO_H
#include "Bots/Bot.hpp"

//#include "../../../GameLogic/Monte_Carlo_Probability_Simulator.cpp"



class BotCenzo : public Bot {

public:
    BotCenzo(const std::string& name, int level) : Bot(name,7) {};
    //matrix raisefunction;

    std::vector<std::vector<float>> raisefunction = std::vector<std::vector<float>>(20, std::vector<float>(20, 0.5));


    //matrix foldfunction;
    std::vector<std::vector<float>> foldfunction = std::vector<std::vector<float>>(20, std::vector<float>(20, 0));

    void Action();
    //matrix adjustraise; what?

};

#endif // BOTCENZO_H

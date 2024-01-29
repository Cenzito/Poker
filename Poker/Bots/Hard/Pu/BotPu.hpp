#ifndef BOTPU_H
#define BOTPU_H

#include "Bots/Bot.hpp"

class BotPu : public Bot
{
public:
    static bool initialized;
    static int ****cfr3, ****cfr4, ****cfr5;
    static int **id_to_card5, *****card_to_id5;
    BotPu(const std::string& name);
    virtual void Action();
};

#endif // BOTPU_H

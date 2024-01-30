#ifndef BOTPU_H
#define BOTPU_H

#include "Bots/Bot.hpp"

class BotPu : public Bot
{
public:
    static bool initialized;
    static int cnt_hand, cnt5, cnt4, cnt3;
    static int ****cfr3, ****cfr4, ****cfr5;
    static int **id_to_card5, *****card_to_id5, **id_to_card4, ****card_to_id4, **id_to_card3, ***card_to_id3;
    static int **id_to_hand, **hand_to_id;
    BotPu(const std::string& name);
    int get_cfr5(int player_num, int handid, int riverid);
    int get_cfr4(int player_num, int handid, int riverid);
    int get_cfr3(int player_num, int handid, int riverid);
    virtual void Action();
};

#endif // BOTPU_H

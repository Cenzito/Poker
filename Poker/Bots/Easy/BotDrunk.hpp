#include "../Bot.hpp"

class BotDrunk : public Bot {
public :
    BotDrunk(const std::string& name, int initialChips) : Bot(name, initialChips, 1) {}
    void action(int minAmount, int type);
};

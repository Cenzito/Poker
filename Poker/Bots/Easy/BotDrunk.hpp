#include "../Bot.hpp"

class BotDrunk : public Bot {
public :
    BotDrunk(const std::string& name) : Bot(name, 1) {}
    void action();
};

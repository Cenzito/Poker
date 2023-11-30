#include "../Bot.hpp"

class BotDrunk : public Bot {
public :
    BotDrunk(const std::string& name, int initialChips) : Bot(name, initialChips, 1) {}
    virtual std::pair<std::string, int> action(const Table* table, int minAmount, int type);
};

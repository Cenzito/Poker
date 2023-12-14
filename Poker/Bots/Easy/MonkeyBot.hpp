#include "../Bot.hpp"

class MonkeyBot : public Bot {
public :
    MonkeyBot(const std::string& name) : Bot(name, 100) {}
    void action(int minAmount, int type);
};

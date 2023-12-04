#include "../Bot.hpp"

class MonkeyBot : public Bot {
public :
    MonkeyBot(const std::string& name, int initialChips) : Bot(name, initialChips, 100) {}
    void action(int minAmount, int type);



};

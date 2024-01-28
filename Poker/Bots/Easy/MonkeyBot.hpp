#include "../Bot.hpp"

class MonkeyBot : public Bot {
public :
    MonkeyBot(const std::string& name) : Bot(name, 2) {}
    virtual void Action();
};

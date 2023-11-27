#include "PokerPlayer.hpp"

class Bot : public PokerPlayer {
public :
    Bot(const std::string& name, int initialChips, int level) : PokerPlayer(name, initialChips) {
        this -> level = level;
    };
protected:
    int level;
    virtual void action(int minAmount, int type);
};
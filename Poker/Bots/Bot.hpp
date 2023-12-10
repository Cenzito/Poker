#include "../GameLogic/PokerPlayer.hpp"

class Bot : public PokerPlayer {
public :
    Bot(const std::string& name, int initialChips, int level) : PokerPlayer(name, initialChips) {
        this -> level = level;
    };

   virtual void action(int minAmount, int type) = 0;

protected:
    int level;
};

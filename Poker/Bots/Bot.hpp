#include "../GameLogic/PokerPlayer.hpp"

class Bot : public PokerPlayer {
public :
    Bot(const std::string& name, int initialChips, int level) : PokerPlayer(name, initialChips) {
        this -> level = level;
    };
//maybe change void to vector to return (actiontype as int, betamount if bet,raise,call etc...)

    virtual void action(int minAmount, int type) = 0;

protected:
    int level;
};

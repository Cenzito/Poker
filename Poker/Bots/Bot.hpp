#include "../GameLogic/PokerPlayerLocal.hpp"

class Bot : public PokerPlayerLocal {
public :
    Bot(const std::string& name, int level) : PokerPlayerLocal(name) {
        this -> level = level;
    };

   virtual int Action();

protected:
    int level;
};

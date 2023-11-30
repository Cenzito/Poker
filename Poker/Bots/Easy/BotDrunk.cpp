#include "BotDrunk.hpp"

std::pair<std::string, int> BotDrunk::action(const Table* table, int minAmount, int type) {
    return std::make_pair("I'm drunkedn.", 0);
}

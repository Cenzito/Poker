#include <string>
#include <vector>
#include "card.hpp"
enum PlayerType {
    Human = 1,
    Bot = 2
};
class Player {
protected:
    PlayerType player_type;
    long long chip; // chips in his hand (excluding bet)
    long long bet; // amount of chips already put in the game
    int id; // id of the player
    std::string name; // name of the player
    std::vector <Card> inHandCards; // size is always 2 when in game
    bool all_in; // 1 = all in
    int in_game; // in which game? 0 = not in any game
public:
    Player(std::string player_name);
    PlayerType get_player_type() const;
    std::string get_player_name() const;
    std::vector<Card> get_inHandCards() const;
    
};
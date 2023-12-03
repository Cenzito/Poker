#ifndef STATISTICAL_ANALYSIS_2_H
#define STATISTICAL_ANALYSIS_2_H

#include <string>
#include <unordered_map>

class PokerWinRate {
public:
    void processHand(const std::string& handData);
    double getWinRate(const std::string& playerName) const;

private:
    struct PlayerStats {
        int wins = 0;
        int games = 0;
    };

    std::unordered_map<std::string, PlayerStats> playerStats;
    void processPlayerResult(const std::string& playerName, bool won);
};

#endif // POKER_WIN_RATE_H

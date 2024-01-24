#include "poker_player.h"

PokerPlayer::PokerPlayer(const std::string& name, int chips)
    : username(name), chips(chips), isFolded(false), currentBet(0) {}

void PokerPlayer::bet(int amount)
{
    if (amount > chips)
        throw std::runtime_error("Not enough chips to bet this amount");
    chips -= amount;
    currentBet += amount;
}

void PokerPlayer::fold()
{
    isFolded = true;
}

bool PokerPlayer::folded()
{
    return isFolded;
}

void PokerPlayer::receiveCard(const Card& card)
{
    hand.push_back(card);
}

std::string PokerPlayer::showHand() const
{
    std::stringstream handStr;
    for (const auto& card : hand)
    {
        handStr << card.toString() << ", ";
    }
    return handStr.str();
}

void PokerPlayer::addChips(int amount)
{
    chips += amount;
}

void PokerPlayer::resetForNewRound()
{
    hand.clear();
    isFolded = false;
    currentBet = 0;
}

std::string PokerPlayer::get_username()
{
    return username;
}

std::string PokerPlayer::get_password()
{
    return password;
}

void PokerPlayer::set_username(std::string username)
{
    this -> username = username;
}

void PokerPlayer::set_password(std::string password)
{
    this -> password = password;
}

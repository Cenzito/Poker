#ifndef POKERPLAYERLOCAL_HPP
#define POKERPLAYERLOCAL_HPP

#include <QCoreApplication>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QEventLoop>

#include "PokerPlayer.hpp"


class PokerPlayerLocal : public PokerPlayer
{
public:
    PokerPlayerLocal(std::string name);


    int Action();


};

#endif // POKERPLAYERLOCAL_HPP

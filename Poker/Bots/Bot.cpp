#include "Bot.hpp"
#include <QTimer>
#include <qdebug.h>

void Bot::Action() {
    if (tableInfo.playerInfo[tableInfo.current_player].name == getName()) {
        // Create a QTimer

        /*
        QTimer timer;

        qDebug() << "acting bot";
        // Connect the QTimer's timeout signal to the delayedSignal slot
        QObject::connect(&timer, &QTimer::timeout, [this]() {
            this->raise_bet(100);
        });

        timer.start(100);
        */

        call_bet();
    }
}


void Bot::call_bet(){
    emit Call();
};
void Bot::fold_bet() {
    emit Fold();
};
void Bot::raise_bet(int amount) {
    qDebug() << "raised dfajkldfj";
    emit Raise(amount);
};

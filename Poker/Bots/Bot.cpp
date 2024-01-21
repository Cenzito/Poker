#include "Bot.hpp"
#include <QTimer>
#include <qdebug.h>

void Bot::Action() {
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
int Bot::find_stack_size(){
    Table table=this->tableInfo;
    int i=0;

    while(i<tableInfo.seats){
        if(table.playerInfo[i].name == this->name)
        {
            return table.playerInfo[i].stack_size;
        }
    }
}

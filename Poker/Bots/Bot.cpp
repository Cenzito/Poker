#include "Bot.hpp"
#include <QTimer>
#include <qdebug.h>

void Bot::call_bet(){
    //qDebug()<<name<<"is calling";
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
        i++;
    }
}

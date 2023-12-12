#include "localgamewindow.h"

LocalGameWindow::LocalGameWindow(QWidget *parent) : GameWindow(parent), game(5)
{

}


void LocalGameWindow::addBot(Bot bot) {
    game.addBot(bot);
}

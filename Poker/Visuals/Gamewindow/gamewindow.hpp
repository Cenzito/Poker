#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "GameLogic/Game.hpp"
#include "GameLogic/PokerPlayer.hpp"
#include "GameLogic/PlayerInfo.hpp"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    const QString Get_image_path(const std::string &suit, const std::string &value, bool back = false); // to display the back call with args ("back", "back", true)
    void update_to_display(PokerPlayer* player, PlayerInfo* info);
    void update_from_display(PokerPlayer* player, PlayerInfo* info);

private slots:

    void on_dealButton_clicked();

    void onPlayButtonClicked();

    void on_BetButton_clicked();

private:
    Ui::GameWindow *ui;

};



#endif // GAMEWINDOW_H

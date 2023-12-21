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
    void update_to_display(PokerPlayer* player);
    void update_from_display();

private slots:

    void on_dealButton_clicked();

    void onPlayButtonClicked();

    void on_BetButton_clicked();

    void display_names_bet(PokerPlayer* player);

    // beginning of switch from name tag to bank display

    void on_line_player1_cursorPositionChanged();

    void on_line_player2_cursorPositionChanged();

    void on_line_player3_cursorPositionChanged();

    void on_line_player4_cursorPositionChanged();

    void on_line_player5_cursorPositionChanged();

    void on_line_player6_cursorPositionChanged();

    void on_line_player7_cursorPositionChanged();

    void on_line_player8_cursorPositionChanged();

    // end of switch from name tag to bank display
private:

    Ui::GameWindow *ui;
    PokerPlayer* game_player;

};



#endif // GAMEWINDOW_H

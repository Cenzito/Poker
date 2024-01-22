#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "GameLogic/PokerPlayer.hpp"
#include "GameLogic/PlayerInfo.hpp"

namespace Ui {
class GameWindow;
}

class GameWindow: public QMainWindow
{
    Q_OBJECT

public:

    explicit GameWindow(QWidget *parent = nullptr, std::string name = "John");
    ~GameWindow();
    const QString Get_image_path(const std::string &suit, const std::string &value, bool back = false); // to display the back call with args ("back", "back", true)

    void update_community_cards();
    void update_middle_card_display(int cardIndex, const Card& card);
    void remove_middle_card_display(int cardIndex);
    void display_names_stacks_bets();

    void display_player_hand();
    void switch_bet_button_on();
    void switch_bet_button_off();
    void switch_players_display();

    PokerPlayer game_player;

private slots:

    virtual void onPlayButtonClicked();

    virtual void on_pushButton_login_clicked();

    virtual void on_pushButton_signin_clicked();

    virtual void onRaiseButtonClicked();

    virtual void onFoldButtonClicked();

    virtual void onCallButtonClicked();

    virtual void updateCallButtonLabel();


    virtual void update_display();

private:
    Ui::GameWindow *ui;

};



#endif // GAMEWINDOW_H

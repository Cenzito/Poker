#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
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

    void update_display();
    void update_community_cards();
    void update_middle_card_display(int cardIndex, const Card& card);
    void remove_middle_card_display(int cardIndex);
    void display_names_stacks_bets();

    void display_player_hand();
    void switch_bet_button_on();
    void switch_bet_button_off();
    void switch_players_display();
    void highlightActivePlayer();
    void display_middle_pot();
    void display_given_cards(PokerPlayer* display_player);
    void display_name_red();
    void preflop_odds();


    PokerPlayer game_player;

private slots:

    void onPlayButtonClicked();

    void onRaiseButtonClicked();

    void onFoldButtonClicked();

    void onCallButtonClicked();

    void updateCallButtonLabel();

    void on_NextRound_clicked();

    void onAddBotClicked();

    void onStartStopButtonClicked();


    void Add_Bot(int index);

private:
    Ui::GameWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *backgroundItem;


};

#endif // GAMEWINDOW_H


#include "gamewindow.hpp"

#include "Visuals/RulesWindow/ruleswindow.h"
#include <QPixmap>
#include "GameLogic/Table.hpp"
#include"GameLogic/PlayerInfo.hpp"
#include "GameLogic/PokerPlayer.hpp"

#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include "ui_gamewindow.h"
#include "GameLogic/Card.hpp"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>



GameWindow::GameWindow(QWidget *parent, std::string name) : game_player(name),
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    // Create a vertical layout
    QVBoxLayout *verticalLayout = new QVBoxLayout(ui->centralwidget);

    QLabel *labelPot = new QLabel;


    connect(ui->pushButton, &QPushButton::clicked, this, &GameWindow::onPlayButtonClicked);
    connect(ui->AddBot_Button, &QPushButton::clicked, this, &GameWindow::onAddBotClicked);
    //connect(ui->FoldButton, &QPushButton::clicked, this, &GameWindow::onFoldButtonClicked(PokerPlayer* game_player));
    connect(ui->FoldButton, &QPushButton::clicked, [=]() {
        onFoldButtonClicked();
    });
    connect(ui->RaiseButton, &QPushButton::clicked, this, &GameWindow::onRaiseButtonClicked);
    connect(ui->CallButton, &QPushButton::clicked, this, &GameWindow::onCallButtonClicked);
    connect(ui->StartStopButton, &QPushButton::clicked, this, &GameWindow::onStartStopButtonClicked);


    /*QImage table_background(":/images/table.png");
    QSize table_background_size = ui->label_table->size();
    ui->label_table->setPixmap(QPixmap::fromImage(table_background).scaled(table_background_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));*/
    //QImage pot_image(":/images/huge_player_stack.png");
    //QSize pot_image_size = ui->label_pot->size();
    //ui->label_pot->setPixmap(QPixmap::fromImage(pot_image).scaled(pot_image_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
\
    QImage potImage(":/images/huge_player_stack.png");
    QImage player_background(":/images/Poker_background.png");

    // Set up the labels with initial images
    ui->label_middlecard1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    labelPot->setPixmap(QPixmap::fromImage(potImage));

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);
    shadowEffect->setOffset(0);
    shadowEffect->setColor(QColor(0, 0, 0, 150));

    QObject::connect(&game_player, &PokerPlayer::callUpdateDisplay, this, &GameWindow::update_display);

    for (int playerNumber = 1; playerNumber <= 8; ++playerNumber) {
        for (int cardNumber = 1; cardNumber <= 2; ++cardNumber) {
            QString labelName = QString("label_player%1_card%2").arg(playerNumber).arg(cardNumber);
            QLabel* playerCardLabel = findChild<QLabel*>(labelName);

            if (playerCardLabel) {
                // Set the image for the player card label
                playerCardLabel->setPixmap(QPixmap(":/images/cards/back_card.png").scaled(playerCardLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                playerCardLabel->setGraphicsEffect(shadowEffect);
            }
        }
    }

    switch_bet_button_off();

    // Add labels to the layout
    verticalLayout->addWidget(labelPot);

    // Set size policies for labels
    labelPot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


GameWindow::~GameWindow()
{
    delete ui;
}

const QString GameWindow::Get_image_path(const std::string &suit, const std::string &value, bool back){

    if (back){
        return ":/images/cards/back_card.png";
    }
    std::string temp =  ":/images/cards/"+std::string(1, suit[0])+"/"+value+".png";
    QString final = QString::fromStdString(temp);
    return final;

}

void GameWindow::onAddBotClicked()
{
    int index = ui->AddBot->currentIndex();
    Add_Bot(index);
}

void GameWindow::Add_Bot(int index) {
    if (game_player.tableInfo.player_num < 8){
        game_player.tableInfo.player_num += 1;
        update_display();
    }
}



void GameWindow::onPlayButtonClicked()
{
    RulesWindow *rulesWindow = new RulesWindow(this) ;
    rulesWindow->show();
}

void GameWindow::onRaiseButtonClicked(){
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));

    emit game_player.Raise(add_bet);
}

void GameWindow::onCallButtonClicked(){ //Reminder: this is check/call button, need to work on changing the name in accordance with the situation, but functionallity should work fine for now
    emit game_player.Call();

}



void GameWindow::onFoldButtonClicked(){
    emit game_player.Fold();
}

void GameWindow::update_display(){
    //qDebug() << "display";
    // Display players hand
    display_player_hand();
    preflop_odds();
  
    // Display names and stacks and put yours in red
    display_name_red();
    display_names_stacks_bets();


    //if you are the current player
    if (game_player.tableInfo.playerInfo[game_player.tableInfo.current_player].name == game_player.getName()) {
        switch_bet_button_on();
    }

    //display middle pot
    display_middle_pot();

    //if (game_player.tableInfo.playerInfo[game_player.tableInfo.current_player].name == game_player.getName()) {
      //  switch_bet_button_on();
    //}
    switch_players_display();
    update_community_cards();
    updateCallButtonLabel();
    displayAllPCards();

}

void GameWindow::onStartStopButtonClicked()
{
    if (ui->StartStopButton->text() == "Start")
    {
        // Start the game
        ui->StartStopButton->setText("Stop");
        //gameLocal.startGame();  // Add a method in GameLocal to start the game
    }
    else
    {
        // Stop the game
        ui->StartStopButton->setText("Start");
        //gameLocal.stopGame();  // Add a method in GameLocal to stop the game
    }

}


void GameWindow::update_community_cards() {
    const std::vector<Card>& communityCards = game_player.tableInfo.communityCards;

    if (communityCards.size() == 0) {
        ui->AddBot->setEnabled(true);
    }
    else {
        ui->AddBot->setEnabled(false);
    }

    //qDebug() << "number center cards: " << communityCards.size();


    // Display the first three community cards initially
    int i = 0;
    for (; i < communityCards.size(); i++) {
        update_middle_card_display(i+1, communityCards[i]);
    }

    for (; i< 5; i++) {
        remove_middle_card_display(i+1);
    }
}

void GameWindow::update_middle_card_display(int cardIndex, const Card& card) {
    QLabel* middleCardLabel = findChild<QLabel*>(QString("label_middlecard%1").arg(cardIndex));
    if (middleCardLabel) {
        //middleCardLabel->show();
        // Get the image path for the card
        QString imagePath = Get_image_path(suitToString(card.getSuit()), std::to_string(card.getValue()), false);
        // Loading and setting the image to the QLabel
        QPixmap image(imagePath);

        QSize labelSize = middleCardLabel->size();

        QPixmap resized_card = image.scaled(labelSize, Qt::KeepAspectRatio);
        middleCardLabel->setPixmap(resized_card);

    }
}

void GameWindow::remove_middle_card_display(int cardIndex) {
    QLabel* middleCardLabel = findChild<QLabel*>(QString("label_middlecard%1").arg(cardIndex));
    if (middleCardLabel) {
        middleCardLabel->clear();
    }
}

void GameWindow::preflop_odds(){
    std::vector<Card> H = game_player.getHand() ; //get the player's hand, to access the cards that need to be displayed
    if (H.size() != 2) {
        return;
    }
    Card C1 = H[0] ;
    Card C2 = H[1] ;
    Suit S1 = C1.getSuit() ;
    Suit S2 = C2.getSuit() ;
    int v1 = C1.getValue() ;
    int v2 = C2.getValue() ;
    bool IsSuited = (S1 == S2);

    int percentage = game_player.get_percentage(v1, v2, IsSuited);

    ui->Preflop_odds->setText(QString::number(percentage));

}
// beginning of display poker hand

  
void GameWindow::display_player_hand(){ // to test
    std::vector<Card> H = game_player.getHand() ; //get the player's hand, to access the cards that need to be displayed
    if (H.size() != 2) {
        return;
    }


    Card C1 = H[0] ;
    Card C2 = H[1] ;
    Suit S1 = C1.getSuit() ;
    Suit S2 = C2.getSuit() ;
    int v1 = C1.getValue() ;
    int v2 = C2.getValue() ;

    // we have the two cards of the player, the suit and value of both those cards
    // following are the path to both corresponding image cards
    QString p1 = Get_image_path(suitToString(S1),std::to_string(v1),false) ;
    QString p2 = Get_image_path(suitToString(S2),std::to_string(v2),false) ;

    //below the two images
    QPixmap first_card(p1) ;
    QPixmap second_card(p2) ;

    QSize labelSize1 = ui->label_card1->size(); // Get the size of the QLabel
    QSize labelSize2 = ui->label_card2->size(); // Get the size of the QLabel
    // Scale the pixmap to fit the QLabel without deforming
    QPixmap resized_card1 = first_card.scaled(labelSize1, Qt::KeepAspectRatio);
    QPixmap resized_card2 = second_card.scaled(labelSize2, Qt::KeepAspectRatio);

    //display of the player's cards
    ui->label_card1->setPixmap(resized_card1) ;
    ui ->label_card2->setPixmap(resized_card2) ;
}
  
  
void GameWindow::switch_bet_button_on(){
    int current_player = game_player.tableInfo.current_player ;
    //auto current_player_info = player->tableInfo.playerInfo[current_player] ;
    //auto current_player_info = player->tableInfo.playerInfo[current_player] ;
    //std::string current_player_info_name = current_player_info.name ;

    std::string player_name = game_player.name ;

    if (ui->RaiseButton->isVisible()==false){ //if the button is already visible, does nothing
        if (game_player.tableInfo.playerInfo.find(current_player)!=game_player.tableInfo.playerInfo.end()){ // check if the player is there
            std::cout << "works" ;
        }
        if (player_name==game_player.tableInfo.playerInfo.at(current_player).name){
            ui->RaiseButton->show() ;
        }
    }
}


void GameWindow::switch_bet_button_off(){
    int current_player = game_player.tableInfo.current_player ;
    std::string player_name = game_player.name ;

    if (ui->RaiseButton->isVisible() == true){ //if the button already hidden, does nothing
        if (player_name == game_player.tableInfo.playerInfo.at(current_player).name){
            ui->RaiseButton->hide() ;
        }
    }
}

void GameWindow::updateCallButtonLabel(){
    //bool condition = /* your condition here */; //SHOULD BE WHETHER TRUE IF SOMEONE PLACES A BET, FALSE IF NO BETS SO FAR IN THE TURN
    bool condition = false;
    if (game_player.tableInfo.current_biggest_bet>0){
        condition = true;
    }
    QString newLabel = (condition) ? "Call" : "Check";
    ui->CallButton->setText(newLabel);
}

// end of switch for buttons

// beginning of switch display players

void GameWindow::switch_players_display(){

    int number_player = game_player.tableInfo.player_num;

    if (number_player < 2){
        ui->line_player2->hide();
        ui->line_bet2->hide();
        ui->label_player2_card1->hide();
        ui->label_player2_card2->hide();

    }else {
        ui->line_player2->show();
        ui->line_bet2->show();
        ui->label_player2_card1->show();
        ui->label_player2_card2->show();

    }
    if (number_player < 3){
        ui->line_player3->hide();
        ui->line_bet3->hide();
        ui->label_player3_card1->hide();
        ui->label_player3_card2->hide();
    }else {
        ui->line_player3->show();
        ui->line_bet3->show();
        ui->label_player3_card1->show();
        ui->label_player3_card2->show();
    }
    if (number_player < 4){
        ui->line_player4->hide();
        ui->line_bet4->hide();
        ui->label_player4_card1->hide();
        ui->label_player4_card2->hide();
    }else {
        ui->line_player4->show();
        ui->line_bet4->show();
        ui->label_player4_card1->show();
        ui->label_player4_card2->show();
    }
    if (number_player < 5){
        ui->line_player5->hide();
        ui->line_bet5->hide();
        ui->label_player5_card1->hide();
        ui->label_player5_card2->hide();
    }else {
        ui->line_player5->show();
        ui->line_bet5->show();
        ui->label_player5_card1->show();
        ui->label_player5_card2->show();
    }
    if (number_player < 6){
        ui->line_player6->hide();
        ui->line_bet6->hide();
        ui->label_player6_card1->hide();
        ui->label_player6_card2->hide();
    }else {
        ui->line_player6->show();
        ui->line_bet6->show();
        ui->label_player6_card1->show();
        ui->label_player6_card2->show();
    }
    if (number_player < 7){
        ui->line_player7->hide();
        ui->line_bet7->hide();
        ui->label_player7_card1->hide();
        ui->label_player7_card2->hide();
    }else {
        ui->line_player7->show();
        ui->line_bet7->show();
        ui->label_player7_card1->show();
        ui->label_player7_card2->show();
    }
    if (number_player < 8){
        ui->line_player8->hide();
        ui->line_bet8->hide();
        ui->label_player8_card1->hide();
        ui->label_player8_card2->hide();
    }else {
        ui->line_player8->show();
        ui->line_bet8->show();
        ui->label_player8_card1->show();
        ui->label_player8_card2->show();
    }
}

// end of switch display players

// beginning of display of names, stacks and bets

void GameWindow::display_names_stacks_bets(){

    //for each additional player, add 1 from the previous sum

    //name of player displayed
    ui ->name_line -> setText(QString::fromStdString(game_player.tableInfo.playerInfo[game_player.tableInfo.current_player].name));

    if (game_player.tableInfo.player_num >= 1){
        std::string playerName1 = game_player.tableInfo.playerInfo[0].name+" | "+std::to_string(game_player.tableInfo.playerInfo[0].stack_size);
        //qDebug() << QString::fromStdString(playerName1);
        ui ->line_player1->setText(QString::fromStdString(playerName1));

        std::string betplayer1 = std::to_string(game_player.tableInfo.playerInfo[0].bet);
        //qDebug() << "bet 1" << QString::fromStdString(betplayer1);
        ui -> line_bet1 -> setText(QString::fromStdString(betplayer1));
    }

    if (game_player.tableInfo.player_num >= 2){
        std::string playerName2 = game_player.tableInfo.playerInfo[1].name+" | "+std::to_string(game_player.tableInfo.playerInfo[1].stack_size);
        ui ->line_player2 ->setText(QString::fromStdString(playerName2));
        std::string betplayer2 = std::to_string(game_player.tableInfo.playerInfo[1].bet);
        //qDebug() << "player 2 bet " << game_player.tableInfo.playerInfo[1].bet;
        ui -> line_bet2 -> setText(QString::fromStdString(betplayer2));
    }

    if (game_player.tableInfo.player_num >= 3){
        std::string playerName3 = game_player.tableInfo.playerInfo[2].name+" | "+std::to_string(game_player.tableInfo.playerInfo[2].stack_size);
        ui ->line_player3 ->setText(QString::fromStdString(playerName3));
        std::string betplayer3 = std::to_string(game_player.tableInfo.playerInfo[2].bet);
        //qDebug() << "bet 3" << QString::fromStdString(betplayer3);
        ui -> line_bet3 -> setText(QString::fromStdString(betplayer3));
    }

    if (game_player.tableInfo.player_num >= 4){
        std::string playerName4 = game_player.tableInfo.playerInfo[3].name+" | "+std::to_string(game_player.tableInfo.playerInfo[3].stack_size);
        ui ->line_player4 ->setText(QString::fromStdString(playerName4));
        std::string betplayer4 = std::to_string(game_player.tableInfo.playerInfo[3].bet);
        ui -> line_bet4 -> setText(QString::fromStdString(betplayer4));
    }

    if (game_player.tableInfo.player_num >= 5){
        std::string playerName5 = game_player.tableInfo.playerInfo[4].name+" | "+std::to_string(game_player.tableInfo.playerInfo[4].stack_size);
        ui ->line_player5 ->setText(QString::fromStdString(playerName5));
        std::string betplayer5 = std::to_string(game_player.tableInfo.playerInfo[4].bet);
        ui -> line_bet5 -> setText(QString::fromStdString(betplayer5));
    }

    if (game_player.tableInfo.player_num >= 6){
        std::string playerName6 = game_player.tableInfo.playerInfo[5].name+" | "+std::to_string(game_player.tableInfo.playerInfo[5].stack_size);
        ui ->line_player6 ->setText(QString::fromStdString(playerName6));
        std::string betplayer6 = std::to_string(game_player.tableInfo.playerInfo[5].bet);
        ui -> line_bet6 -> setText(QString::fromStdString(betplayer6));
    }

    if (game_player.tableInfo.player_num >= 7){
        std::string playerName7 = game_player.tableInfo.playerInfo[6].name+" | "+std::to_string(game_player.tableInfo.playerInfo[6].stack_size);
        ui ->line_player7 ->setText(QString::fromStdString(playerName7));
        std::string betplayer7 = std::to_string(game_player.tableInfo.playerInfo[6].bet);
        ui -> line_bet7 -> setText(QString::fromStdString(betplayer7));
    }

    if (game_player.tableInfo.player_num >= 8){
        std::string playerName8 = game_player.tableInfo.playerInfo[7].name+" | "+std::to_string(game_player.tableInfo.playerInfo[7].stack_size);
        ui ->line_player8 ->setText(QString::fromStdString(playerName8));
        std::string betplayer8 = std::to_string(game_player.tableInfo.playerInfo[7].bet);
        ui -> line_bet8 -> setText(QString::fromStdString(betplayer8));
    }

}

// beginning of highlight current player

void GameWindow::highlightActivePlayer() {

    //current player
    std::string name = game_player.getName();

    // Loop through all player labels
    for (int i = 1; i <= 8; ++i) {
        QLabel* playerLabel = findChild<QLabel*>(QString("line_player%1").arg(i));
        QString labelText = playerLabel->text();

        //checking which player is active
        if (labelText.toStdString() == name) {

            // Highlight the active player's label
            playerLabel->setStyleSheet("border: 2px solid yellow;"); // the style
        }
    }
}
// end of highlight current player

// start of display and update middle pot

void GameWindow::display_middle_pot(){
    int middle_pot = game_player.tableInfo.pot ;
    QFont font = ui->label_pot->font();
    font.setBold(true) ;
    ui->label_pot->setFont(font) ;
    ui->label_pot->setText(QString::number(middle_pot)) ; // potentially change label
}

// end of display and update middle pot

void GameWindow::on_NextRound_clicked()
{
    //clear table
    //potsize = 0
    //update player states for new round
    //shuffle deck
    //update  UI
    //check Game status

}

// start of display a given player's cards
void GameWindow::displayAllPCards() {
    if (game_player.tableInfo.player_num >= 1 && game_player.tableInfo.playerInfo[0].cards.size() == 2){
        Card card1 = game_player.tableInfo.playerInfo[0].cards[0];
        Card card2 = game_player.tableInfo.playerInfo[0].cards[1];
        Suit suit1 = card1.getSuit();
        Suit suit2 = card2.getSuit();
        int value1 = card1.getValue();
        int value2 = card2.getValue();
        QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
        QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
        QImage image1(path1);
        QImage image2(path2);

        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player1_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player1_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (game_player.tableInfo.player_num >= 2&& game_player.tableInfo.playerInfo[1].cards.size() == 2){

        Card card1 = game_player.tableInfo.playerInfo[1].cards[0];
        Card card2 = game_player.tableInfo.playerInfo[1].cards[1];
        Suit suit1 = card1.getSuit();
        Suit suit2 = card2.getSuit();
        int value1 = card1.getValue();
        int value2 = card2.getValue();
        QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
        QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
        QImage image1(path1);
        QImage image2(path2);

        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player2_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player2_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (game_player.tableInfo.player_num >= 3&& game_player.tableInfo.playerInfo[2].cards.size() == 2){
        Card card1 = game_player.tableInfo.playerInfo[2].cards[0];
        Card card2 = game_player.tableInfo.playerInfo[2].cards[1];
        Suit suit1 = card1.getSuit();
        Suit suit2 = card2.getSuit();
        int value1 = card1.getValue();
        int value2 = card2.getValue();
        QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
        QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
        QImage image1(path1);
        QImage image2(path2);

        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player3_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player3_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (game_player.tableInfo.player_num >= 4&& game_player.tableInfo.playerInfo[3].cards.size() == 2){
        Card card1 = game_player.tableInfo.playerInfo[3].cards[0];
        Card card2 = game_player.tableInfo.playerInfo[3].cards[1];
        Suit suit1 = card1.getSuit();
        Suit suit2 = card2.getSuit();
        int value1 = card1.getValue();
        int value2 = card2.getValue();
        QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
        QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
        QImage image1(path1);
        QImage image2(path2);

        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player4_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player4_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (game_player.tableInfo.player_num >= 5&& game_player.tableInfo.playerInfo[4].cards.size() == 2){
        Card card1 = game_player.tableInfo.playerInfo[4].cards[0];
        Card card2 = game_player.tableInfo.playerInfo[4].cards[1];
        Suit suit1 = card1.getSuit();
        Suit suit2 = card2.getSuit();
        int value1 = card1.getValue();
        int value2 = card2.getValue();
        QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
        QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
        QImage image1(path1);
        QImage image2(path2);

        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player5_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player5_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (game_player.tableInfo.player_num >= 6&& game_player.tableInfo.playerInfo[5].cards.size() == 2){
        Card card1 = game_player.tableInfo.playerInfo[5].cards[0];
        Card card2 = game_player.tableInfo.playerInfo[5].cards[1];
        Suit suit1 = card1.getSuit();
        Suit suit2 = card2.getSuit();
        int value1 = card1.getValue();
        int value2 = card2.getValue();
        QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
        QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
        QImage image1(path1);
        QImage image2(path2);

        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player6_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player6_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (game_player.tableInfo.player_num >= 7&& game_player.tableInfo.playerInfo[6].cards.size() == 2){
        Card card1 = game_player.tableInfo.playerInfo[6].cards[0];
        Card card2 = game_player.tableInfo.playerInfo[6].cards[1];
        Suit suit1 = card1.getSuit();
        Suit suit2 = card2.getSuit();
        int value1 = card1.getValue();
        int value2 = card2.getValue();
        QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
        QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
        QImage image1(path1);
        QImage image2(path2);

        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player7_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player7_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    if (game_player.tableInfo.player_num >= 8&& game_player.tableInfo.playerInfo[7].cards.size() == 2){
        Card card1 = game_player.tableInfo.playerInfo[7].cards[0];
        Card card2 = game_player.tableInfo.playerInfo[7].cards[1];
        Suit suit1 = card1.getSuit();
        Suit suit2 = card2.getSuit();
        int value1 = card1.getValue();
        int value2 = card2.getValue();
        QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
        QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
        QImage image1(path1);
        QImage image2(path2);

        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player8_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player8_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void GameWindow::display_given_cards(PokerPlayer* display_player){

    int num = display_player->tableInfo.current_player;
    Card card1 = display_player->hand[0];
    Card card2 = display_player->hand[1];
    Suit suit1 = card1.getSuit();
    Suit suit2 = card2.getSuit();
    int value1 = card1.getValue();
    int value2 = card2.getValue();
    QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
    QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
    QImage image1(path1);
    QImage image2(path2);

    if(num == 1){
        QSize size1 = ui->label_player1_card1->size();
        QSize size2 = ui->label_player1_card2->size();

        ui->label_player1_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player1_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if(num == 2){
        QSize size1 = ui->label_player2_card1->size();
        QSize size2 = ui->label_player2_card2->size();

        ui->label_player2_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player2_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if(num == 3){
        QSize size1 = ui->label_player3_card1->size();
        QSize size2 = ui->label_player3_card2->size();

        ui->label_player3_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player3_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if(num == 4){
        QSize size1 = ui->label_player4_card1->size();
        QSize size2 = ui->label_player4_card2->size();

        ui->label_player4_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player4_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if(num == 5){
        QSize size1 = ui->label_player5_card1->size();
        QSize size2 = ui->label_player5_card2->size();

        ui->label_player5_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player5_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if(num == 6){
        QSize size1 = ui->label_player6_card1->size();
        QSize size2 = ui->label_player6_card2->size();

        ui->label_player6_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player6_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if(num == 7){
        QSize size1 = ui->label_player7_card1->size();
        QSize size2 = ui->label_player7_card2->size();

        ui->label_player7_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player7_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if(num == 8){
        QSize size1 = ui->label_player8_card1->size();
        QSize size2 = ui->label_player8_card2->size();

        ui->label_player8_card1->setPixmap(QPixmap::fromImage(image1).scaled(size1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_player8_card2->setPixmap(QPixmap::fromImage(image2).scaled(size2, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

// end of display a given player's cards

// start display name red

void GameWindow::display_name_red(){

    int num = game_player.tableInfo.current_player;

    if(num == 1){
        ui->line_player1->setStyleSheet("color : red;");
    }
    if(num == 2){
        ui->line_player2->setStyleSheet("color : red;");
    }
    if(num == 3){
        ui->line_player3->setStyleSheet("color : red;");
    }
    if(num == 4){
        ui->line_player4->setStyleSheet("color : red;");
    }
    if(num == 5){
        ui->line_player5->setStyleSheet("color : red;");
    }
    if(num == 6){
        ui->line_player6->setStyleSheet("color : red;");
    }
    if(num == 7){
        ui->line_player7->setStyleSheet("color : red;");
    }
    if(num == 8){
        ui->line_player8->setStyleSheet("color : red;");
    }

}

// end display name red


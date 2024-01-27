
#include "gamewindow.hpp"
#include <vector>
#include "Visuals/RulesWindow/ruleswindow.h"
#include <QPixmap>
#include "GameLogic/Table.hpp"
#include"GameLogic/PlayerInfo.hpp"
#include "GameLogic/PokerPlayer.hpp"
#include "GameLogic/PokerHand.hpp"
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


    connect(ui->pushButton, &QPushButton::clicked, this, &GameWindow::onRulesButtonClicked);
    connect(ui->AddBot_Button, &QPushButton::clicked, this, &GameWindow::onAddBotClicked);
    //connect(ui->FoldButton, &QPushButton::clicked, this, &GameWindow::onFoldButtonClicked(PokerPlayer* game_player));
    connect(ui->FoldButton, &QPushButton::clicked, [=]() {
        onFoldButtonClicked();
    });
    connect(ui->RaiseButton, &QPushButton::clicked, this, &GameWindow::onRaiseButtonClicked);
    connect(ui->CallButton, &QPushButton::clicked, this, &GameWindow::onCallButtonClicked);
    connect(ui->NextRound, &QPushButton::clicked, this, &GameWindow::onNextRoundButtonClicked);


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



/*
    Those are the functions to handle the button presses
*/

/*
 *  onAddBotClicked(): add a bot to the game
*/
void GameWindow::onAddBotClicked()
{
    return;
}


/*
 *  onRulesButtonClicked(): Open the rules window
 *  It is kinda ugly but it is what it is
*/
void GameWindow::onRulesButtonClicked()
{
    RulesWindow *rulesWindow = new RulesWindow(this) ;
    rulesWindow->show();
}


/*
 * onRaiseButtonClicked(): Raise by the amount typed
*/
void GameWindow::onRaiseButtonClicked(){
    int add_bet = ui->raise_box->value();
    int current = (ui->cumulative_bet_line->text()).toInt();
    ui->cumulative_bet_line->setText(QString::number(add_bet+current));

    emit game_player.Raise(add_bet);
}

/*
 * onCallButtonClicked(): CALL
*/
void GameWindow::onCallButtonClicked(){ //Reminder: this is check/call button, need to work on changing the name in accordance with the situation, but functionallity should work fine for now
    emit game_player.Call();

}

/*
 * onFoldButtonClicked(): FOLD
*/
void GameWindow::onFoldButtonClicked(){
    emit game_player.Fold();
}

/*
 * onNextRoundButtonClicked(): Got to next round
 * This button gives the player time to see everyone's cards and decide when to continue playing
 * otherwise it would be immediate
*/
void GameWindow::onNextRoundButtonClicked()
{
    emit game_player.nextGame();
    for (int playerNumber = 1; playerNumber <= 8; ++playerNumber) {
        for (int cardNumber = 1; cardNumber <= 2; ++cardNumber) {
            QString labelName = QString("label_player%1_card%2").arg(playerNumber).arg(cardNumber);
            QLabel* playerCardLabel = findChild<QLabel*>(labelName);

            if (playerCardLabel) {
                // Set the image for the player card label
                playerCardLabel->setPixmap(QPixmap(":/images/cards/back_card.png").scaled(playerCardLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    }


}

void GameWindow::player_hand_description() {
    std::vector<Card> commCards = game_player.tableInfo.communityCards;
    const std::vector<Card>& playerCards = game_player.getHand();

    // Make a copy of playerCards
    std::vector<Card> playerCardsCopy = playerCards;

    // Concatenate the copied playerCards to commCards
    commCards.insert(commCards.end(), playerCardsCopy.begin(), playerCardsCopy.end());
    /*
    for (Card i : communityCards) {
        qDebug() <<QString::i;
    }
    */
    PokerHand hand = commCards;
    PokerCombinations combination = hand.get_combination();
    QString hand_name; // Declare the variable outside of the if-else blocks
    if (combination == PokerCombinations::RoyalFlush) {
        hand_name = "Royal Flush";
    }
    else if (combination == PokerCombinations::StraightFlush) {
        hand_name = "Straight Flush";
    }
    else if (combination == PokerCombinations::FourOfAKind) {
        hand_name = "Four of a kind";
    }
    else if (combination == PokerCombinations::FullHouse) {
        hand_name = "Full House";
    }
    else if (combination == PokerCombinations::Flush) {
        hand_name = "Flush";
    }
    else if (combination == PokerCombinations::Straight) {
        hand_name = "Straight";
    }
    else if (combination == PokerCombinations::ThreeOfAKind) {
        hand_name = "Three of a kind";
    }
    else if (combination == PokerCombinations::TwoPairs) {
        hand_name = "Two Pairs";
    }
    else if (combination == PokerCombinations::Pair) {
        hand_name = "Pair";
    }
    else {
        hand_name = "High Card";
    }
    ui->hand_display->setText(hand_name);
    qDebug() <<hand_name;
}
/*
 * Those are functions to handle changes in the display.
 * When a change to the Player's table happens, update_display is called.
 * It then updates the entire screen
 * For efficiency, it would be good to update only the modified elements
*/

/*
 * update_display: Main function to update the display, calls all the other functions
*/
void GameWindow::update_display(){
    //qDebug() << "display";
    // Display players hand
    display_player_hand();
    preflop_odds();
    player_hand_description();

    // Display names and stacks and put yours in red
    display_name_red();
    display_names_stacks_bets();


    //if you are the current player
    if (game_player.tableInfo.playerInfo[game_player.tableInfo.current_player].name == game_player.getName()) {
        switch_bet_button_on();
    }
    else {
        switch_bet_button_off();
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
    QApplication::processEvents();

}



/*
 * Updates the cards in the middle
*/
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

/*
 * update_middle_card_display(int, const Card&): updates individual card in the middle bases on the parameters if is called with
 * Is called by update_community_cards()
*/
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

/*
 * remove_middle_card_display(int): Remove display of a card in the middle (if there is no card)
 * Is called by update_community_cards()
*/
void GameWindow::remove_middle_card_display(int cardIndex) {
    QLabel* middleCardLabel = findChild<QLabel*>(QString("label_middlecard%1").arg(cardIndex));
    if (middleCardLabel) {
        middleCardLabel->clear();
    }
}


/*
 * preflop_odds() : computes the "odds" you have of winning based only on your two initial cards and no more information
 * This computation is based on a prewritted table taking into account interactions between two players only
 * It is only shown as an indication to the player
*/
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
    QString text = "Preflop odds (Heads up):  " + QString::number(percentage) + " %";

    ui->Preflop_odds->setText(text);


}


/*
 * display_player_hand() : display the cards the player currently has
 *
*/
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

/*
 * switch_bet_button_on() : display the bet button when it is our turn to bet
 *
*/
void GameWindow::switch_bet_button_on(){
    ui->RaiseButton->show();
    ui->FoldButton->show() ;
    ui->CallButton->show();
}

/*
 * switch_bet_button_off() : remove display of the bet button when it is clicked
 *
*/

void GameWindow::switch_bet_button_off(){
    ui->RaiseButton->hide();
    ui->FoldButton->hide() ;
    ui->CallButton->hide();
}


/*
 * updateCallButtonLabel() : call or check on the button
 *
*/

void GameWindow::updateCallButtonLabel(){
    //bool condition = /* your condition here */; //SHOULD BE WHETHER TRUE IF SOMEONE PLACES A BET, FALSE IF NO BETS SO FAR IN THE TURN
    bool condition = false;
    if (game_player.tableInfo.current_biggest_bet>0){
        condition = true;
    }
    QString newLabel = (condition) ? "Call" : "Check";
    ui->CallButton->setText(newLabel);
}

/*
 * switch_players_display(): Display the information of a player if this player is in the game
 * It is based on the number of player and doesn't show an empty nametag if there is no player
 *
*/
void GameWindow::switch_players_display() {
    int numPlayers = game_player.tableInfo.player_num;
    for (int i = 2; i <= 8; ++i) {
        QLineEdit* line_player = findChild<QLineEdit*>(QString("line_player%1").arg(i));
        QLineEdit* line_bet = findChild<QLineEdit*>(QString("line_bet%1").arg(i));
        QLabel* label_card1 = findChild<QLabel*>(QString("label_player%1_card1").arg(i));
        QLabel* label_card2 = findChild<QLabel*>(QString("label_player%1_card2").arg(i));

        if (i <= numPlayers) {
            line_player->show();
            line_bet->show();
            label_card1->show();
            label_card2->show();
        } else {
            line_player->hide();
            line_bet->hide();
            label_card1->hide();
            label_card2->hide();
        }
    }
}


/*
 * display_names_stacks_bets(): as the name suggests, displays the name, stack and bet of the players
 *
*/

void GameWindow::display_names_stacks_bets() {
    // Display current player name
    ui->name_line->setText(QString::fromStdString(game_player.tableInfo.playerInfo[game_player.tableInfo.current_player].name));

    // Loop through player numbers
    for (int i = 0; i < game_player.tableInfo.player_num && i < 8; ++i) {
        std::string playerName = game_player.tableInfo.playerInfo[i].name + " | " + std::to_string(game_player.tableInfo.playerInfo[i].stack_size);
        QLineEdit* line_player = findChild<QLineEdit*>(QString("line_player%1").arg(i + 1));
        QLineEdit* line_bet = findChild<QLineEdit*>(QString("line_bet%1").arg(i + 1));

        // Set player name and stack size
        if (line_player)
            line_player->setText(QString::fromStdString(playerName));

        // Set player bet
        if (line_bet)
            line_bet->setText(QString::fromStdString(std::to_string(game_player.tableInfo.playerInfo[i].bet)));
    }
}


/*
 * highlightActivePlayer(): put a border on the box of the player that is currently playing
 *
*/
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
            playerLabel->setStyleSheet("border: 20px solid yellow;"); // the style
        }
    }
}

/*
 * display_middle_pot(): display sum in the pot
*/
void GameWindow::display_middle_pot(){
    int middle_pot = game_player.tableInfo.pot ;
    QFont font = ui->pot_amount->font();
    font.setBold(true) ;
    ui->pot_amount->setFont(font) ;
    ui->pot_amount->setText("Pot size : " + QString::number(middle_pot) + "chips") ; // potentially change label
    int non_bet_chips = 0;
    for (int i = 0; i < game_player.tableInfo.player_num && i < 8; ++i) {
        non_bet_chips = non_bet_chips + game_player.tableInfo.playerInfo[i].stack_size;
    }
    if (middle_pot >= non_bet_chips){
        QImage image(":/images/huge_player_stack.png");
        QSize labelSize = ui->pot_image->size(); // Get the size of the QLabel
        // Scale the pixmap to fit the QLabel without deforming
        QPixmap resized_pot = QPixmap::fromImage(image).scaled(labelSize, Qt::KeepAspectRatio);
        ui->pot_image->setPixmap(resized_pot) ;

    }
    else {
        QImage image(":/images/player_stack.png");
        QSize labelSize = ui->pot_image->size(); // Get the size of the QLabel
        // Scale the pixmap to fit the QLabel without deforming
        QPixmap resized_pot = QPixmap::fromImage(image).scaled(labelSize, Qt::KeepAspectRatio);
        ui->pot_image->setPixmap(resized_pot) ;
    }

}

// end of display and update middle pot


/*
 * displayCardP(): Display the cards of a specific player
 * is called by displayAllPCards();
 *
*/
void GameWindow::displayCardP(int player) {
    Card card1 = game_player.tableInfo.playerInfo[player].cards[0];
    Card card2 = game_player.tableInfo.playerInfo[player].cards[1];
    Suit suit1 = card1.getSuit();
    Suit suit2 = card2.getSuit();
    int value1 = card1.getValue();
    int value2 = card2.getValue();
    qDebug() << Get_image_path(suitToString(suit1),std::to_string(value1),false);
    qDebug() << Get_image_path(suitToString(suit2),std::to_string(value2),false);
    QString path1 = Get_image_path(suitToString(suit1),std::to_string(value1),false);
    QString path2 = Get_image_path(suitToString(suit2),std::to_string(value2),false);
    QImage image1(path1);
    QImage image2(path2);
    QString labelName1 = QString("label_player%1_card1").arg(player+1);
    QString labelName2 = QString("label_player%1_card2").arg(player+1);
    QLabel* playerCardLabel1 = findChild<QLabel*>(labelName1);
    QLabel* playerCardLabel2 = findChild<QLabel*>(labelName2);
    if (playerCardLabel1) {
        playerCardLabel1->setPixmap(QPixmap::fromImage(image1).scaled(playerCardLabel1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if (playerCardLabel2) {
        playerCardLabel2->setPixmap(QPixmap::fromImage(image2).scaled(playerCardLabel2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
// start of display a given player's cards

/*
 * displayAllPCards(): Display the cards of all the players
 * This is used at the end of a round to see who wins
 *
*/
void GameWindow::displayAllPCards() {
    for (int i=0; i <game_player.tableInfo.player_num;i++) {
        if (game_player.tableInfo.playerInfo[i].cards.size() == 2) {
            displayCardP(i);
        }
    }
}


/*
 *  display_name_red(): as the name suggests, displays the names in red
 *  not really sure why?
 *
 *
*/
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


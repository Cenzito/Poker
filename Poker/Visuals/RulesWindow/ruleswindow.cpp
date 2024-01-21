#include "ruleswindow.h"
#include "qgraphicseffect.h"
#include "qlabel.h"
#include "ui_ruleswindow.h"

#include <QResource>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QPalette>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

RulesWindow::RulesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RulesWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &RulesWindow::CloseRulesWindow);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);

    tabWidget = new QTabWidget(this);
    tab1 = new QTextBrowser(this);
    tab2 = new QTextBrowser(this);

    tabWidget->addTab(tab1, "Rules");
    tabWidget->addTab(tab2, "Hands");

    layout->addWidget(tabWidget);

    // Set stretch factors for resizing
    layout->setStretchFactor(tabWidget, 1);
    layout->setStretchFactor(tab1, 1);
    layout->setStretchFactor(tab2, 1); //got help from the internet here (for finding a way to resize the window)

    QString rules_of_poker = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><meta http-equiv='Content-Style-Type' content='text/css'><title></title><meta name='Generator' content='Cocoa HTML Writer'><meta name='CocoaVersion' content='2299.7'><style type='text/css'> p.p1 {margin: 0.0px 0.0px 0.0px 0.0px; text-align: center; font: 11.0px 'Comic Sans MS'; color: #000000} p.p2 {margin: 0.0px 0.0px 0.0px 0.0px; text-align: center; font: 11.0px 'Comic Sans MS'; color: #000000; min-height: 15.0px} p.p3 {margin: 0.0px 0.0px 0.0px 0.0px; font: 11.0px 'Comic Sans MS'; color: #000000} p.p4 {margin: 0.0px 0.0px 0.0px 0.0px; font: 11.0px 'Comic Sans MS'; color: #000000; min-height: 15.0px}p.p5 {margin: 0.0px 0.0px 0.0px 0.0px; font: 12.0px 'Comic Sans MS'; -webkit-text-stroke: #000000; min-height: 16.0px} span.s1 {text-decoration: underline} span.s2 {font-kerning: none}</style></head><body>"
                             "<p class='p1'><b>RULES OF POKER</b></p><p class='p2'><b></b><br></p><p class='p3'>Poker is an individual game consisting of several successive rounds of betting.</p><p class='p4'><br></p><p class='p3'><span class='s1'>First Round:</span></p><p class='p4'><br></p><p class='p3'>In each round, the cards are shuffled, and each player receives two cards, one at a time. The remaining cards form the deck.</p><p class='p4'><br></p><p class='p3'>Each player is dealt two hole cards. The first player initiates the round by making a 'forced bet', called the blind. The round then proceeds clockwise. Players act based on their assessment of their hand, considering that a hand consists of five cards, and three new cards are placed on the table. Players can choose to call the previous bet, raise the bet, check, or fold.</p><p class='p4'><br></p><p class='p3'><b>Fold</b>: The player withdraws from the current round, losing the amount bet so far.</p>"
                             "<p class='p3'><b>Check</b>: The player waits to see the actions of other players.</p><p class='p3'><b>Call</b>: The player calls the current maximum bet. Optionally, the player can raise the bet.</p><p class='p4'><br></p><p class='p3'>The round concludes when all players have either folded or called the last bet.</p><p class='p4'><br></p><p class='p3'><span class='s1'>Flop:</span></p><p class='p4'><br></p><p class='p3'>One card is discarded, and three cards are revealed on the table, and they start forming the board. The starting player for each round changes clockwise. The round proceeds similarly to the first one.</p><p class='p4'><br></p><p class='p3'><span class='s1'>Turn and River:</span></p><p class='p4'><br></p>"
                             "<p class='p3'>At the beginning of both the turn and the river, one card is discarded, and one is added to the board. By the river, there are five cards on the board  . The rounds unfold similarly to the earlier rounds.</p><p class='p4'><br></p><p class='p3'><span class='s1'>The Showdown:</span></p><p class='p4'><br></p><p class='p3'>If only one player remains in the round (i.e., all other players have folded), that player collects the pot without revealing their hand. This feature allows for 'bluffing': a player can match or increase bets while holding a weak hand, hoping that players with stronger hands will fold.</p><p class='p3'>If more than one player remains after the final betting round, all hands are revealed, and the player with the winning hand claims the pot.</p>"
                             "<p class='p5'><span class='s2'></span><br></p></body></html>";

    tab1 -> setHtml(rules_of_poker);

    QString hands_in_poker = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><meta http-equiv='Content-Style-Type' content='text/css'><title></title><meta name='Generator' content='Cocoa HTML Writer'><meta name='CocoaVersion' content='2299.7'><style type='text/css'> p.p1 {margin: 0.0px 0.0px 0.0px 0.0px; text-align: center; font: 11.0px 'Comic Sans MS'; color: #000000} p.p2 {margin: 0.0px 0.0px 0.0px 0.0px; text-align: center; font: 11.0px 'Comic Sans MS'; color: #000000; min-height: 15.0px} p.p3 {margin: 0.0px 0.0px 0.0px 0.0px; font: 11.0px 'Comic Sans MS'; color: #000000} p.p4 {margin: 0.0px 0.0px 0.0px 0.0px; font: 11.0px 'Comic Sans MS'; color: #000000; min-height: 15.0px}p.p5 {margin: 0.0px 0.0px 0.0px 0.0px; font: 12.0px 'Comic Sans MS'; -webkit-text-stroke: #000000; min-height: 16.0px} span.s1 {text-decoration: underline} span.s2 {font-kerning: none}</style></head>"
                              "<body><p class='p1'><b>HANDS RANKED FROM LOWEST TO HIGHEST</b></p><p class='p4'><br><b>High Card (no pair)</b><br></p><p class='p3'> No two cards have the same rank, the five cards are not in sequence, and the five cards are not te same suit.<br>When comparing the same types of hands, the higher-ranking card defeats the lower ranking card <br> <u>Ex.</u>  K♥ J♣ 8♣ 7♦ 3♠  (“King High’)<br><img src=:/images/cards/H/13.png width=50 />  <img src=:/images/cards/C/11.png width=50 />  <img src=:/images/cards/C/8.png width=50/>  <img src=:/images/cards/D/7.png width=50 />  <img src=:/images/cards/S/3.png width=50 /> </p>"
                              "<p class='p3'><b>One Pair</b><br><br>Two cards of the same rank, plus three other unmatched cards.<br>When comparing the sames types of hands, the higher-ranking pairs defeat the lower-ranking pairs.<br><u>Ex.</u> 4♥ 4♠ K♠ 10♥ 5♠ (Pair of Fours)<br></p>"
                              "<p class='p3'><b>Two Pairs</b><br><br>Two cards of the same rank, plus two cards of another rank (that match each other, but not the first pair), plus one ummatched card.<br>When comparing same types of hands, higher ranking pair of the two defeats lower ranking pair<br><u>Ex.</u> J♥ J♣ 4♣ 4♠ 9♥ (“Jacks over Fours’)<br></p>"
                              "<p class='p3'><b>Three of a Kind</b><br><br>Three cards of the same rank, plus two unmatched cards.<br>When comparing the same types of hands, the higher-value three of a kind defeats the lower-value three of a kind.<br><u>Ex.</u> 2♦ 2♠ 2♣ K♠ 6♥<br></p>"
                              "<p class='p3'><b>Straight</b><br><br>Contains five cards of sequential rank but in more than one suit.<br> Two straights are ranked by comparing the highest card of each. Two straights with the same high card are of equal value.<br><u>Ex.</u> Q♣ J♠ 10♠ 9♥ 8♥ (“Queen-High Straight’)<br></p> "
                              "<p class='p3'><b>Flush</b><br><br>Contains five cards of the same suit, not in rank or sequence.<br>When comparing the same types of hands, the highest-ranking card wins.<br><u>Ex.</u> Q♣ 10♣ 7♣ 6♣ 4♣ (“Queen-High Flush)<br></p> "
                              "<p class='p3'><b>Full House</b><br><br>Contains three matching cards of one rank and two matching cards of another rank.<br>When comparing the same types of hands, the higher-ranking set of three wins.<br><u>Ex.</u> 3♣ 3♠ 3♦ 6♣ 6♥ (“Threes over Sixes’)<br></p> "
                              "<p class='p3'><b>Four of a Kind</b><br><br>Contains four cards of one rank and an unmatched card of another rank.<br>When comparing the same types of hands, higher-ranking quads defeat lower-ranking ones.<br><u>Ex.</u> 4♣ 4♠ 4♦ 4♥ 6♣<br></p> "
                              "<p class='p3'><b>Straight Flush</b><br><br>Contains five cards in sequence, all of the same suit (therefore, both a straight and a flush).<br>Compare hands by looking at their highest card. Two identical straight flushes tie since suits have no value.<br><u>Ex.</u> Q♣ J♣ 10♣ 9♣ 8♣<br></p> "
                              "<p class='p3'><b>Royal Flush</b><br><br>The highest poker hand, containing an Ace, King, Queen, Jack, and a 10, all of the same suit.<br><u>Ex.</u> 10♥ J♥ Q♥ K♥ A♥<br></p> "
                              "</body></html>";

    tab2 -> setHtml(hands_in_poker) ;
    QString styleSheet = "background-color: rgb(60, 122, 28);"
                         "background-image: url(:/images/Poker_background.png);"
                         "background-repeat: repeat-y;";
    QString styleSheet2 = "background-color: rgb(60, 122, 28);"
                         "background-image: url(:/images/Poker_background.png);"
                         "background-repeat: repeat-y;";

    tab1->setStyleSheet(styleSheet);
    tab2->setStyleSheet(styleSheet2);

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(30);
    shadowEffect->setOffset(0);
    shadowEffect->setColor(QColor(0, 0, 0, 150));
    tab1->setGraphicsEffect(shadowEffect);
    tab2->setGraphicsEffect(shadowEffect);

    setStyleSheet("background-color:rgb(60, 122, 28);");
    setAutoFillBackground(true);
}

RulesWindow::~RulesWindow()
{
    delete ui;
}

void RulesWindow::CloseRulesWindow()
{
    this -> close() ;
}

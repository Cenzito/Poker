#include "ruleswindow.h"
#include "ui_ruleswindow.h"

#include <QResource>
#include <QFile>
#include <QTextStream>

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

    tabWidget->addTab(tab1, "Tab 1");
    tabWidget->addTab(tab2, "Tab 2");

    layout->addWidget(tabWidget);

    // Set stretch factors for resizing
    layout->setStretchFactor(tabWidget, 1);
    layout->setStretchFactor(tab1, 1);
    layout->setStretchFactor(tab2, 1); //got help from the internet here (for finding a way to resize the window)

    QString rules_of_poker = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><meta http-equiv='Content-Style-Type' content='text/css'><title></title><meta name='Generator' content='Cocoa HTML Writer'><meta name='CocoaVersion' content='2299.7'><style type='text/css'> p.p1 {margin: 0.0px 0.0px 0.0px 0.0px; text-align: center; font: 11.0px 'Comic Sans MS'; color: #000000} p.p2 {margin: 0.0px 0.0px 0.0px 0.0px; text-align: center; font: 11.0px 'Comic Sans MS'; color: #000000; min-height: 15.0px} p.p3 {margin: 0.0px 0.0px 0.0px 0.0px; font: 11.0px 'Comic Sans MS'; color: #000000} p.p4 {margin: 0.0px 0.0px 0.0px 0.0px; font: 11.0px 'Comic Sans MS'; color: #000000; min-height: 15.0px}p.p5 {margin: 0.0px 0.0px 0.0px 0.0px; font: 12.0px 'Comic Sans MS'; -webkit-text-stroke: #000000; min-height: 16.0px} span.s1 {text-decoration: underline} span.s2 {font-kerning: none}</style></head><body><p class='p1'><b>RULES OF POKER</b></p><p class='p2'><b></b><br></p><p class='p3'>Poker is an individual game consisting of several successive rounds of betting.</p><p class='p4'><br></p><p class='p3'><span class='s1'>First Round:</span></p><p class='p4'><br></p><p class='p3'>In each round, the cards are shuffled, and each player receives two cards, one at a time. The remaining cards form the deck.</p><p class='p4'><br></p><p class='p3'>Each player is dealt two hole cards. The first player initiates the round by making a 'forced bet.' The round then proceeds clockwise. Players act based on their assessment of their hand, considering that a hand consists of five cards, and three new cards are placed on the table. Players can choose to match the previous bet, raise the bet, check, or fold.</p><p class='p4'><br></p><p class='p3'><b>Fold</b>: The player withdraws from the current round, losing the amount bet so far.</p><p class='p3'><b>Check</b>: The player waits to see the actions of other players.</p><p class='p3'><b>Match</b>: The player matches the current maximum bet. Optionally, the player can raise the bet.</p><p class='p4'><br></p><p class='p3'>The round concludes when all players have either folded or called the last bet.</p><p class='p4'><br></p><p class='p3'><span class='s1'>Second Round:</span></p><p class='p4'><br></p><p class='p3'>One card is discarded, and three cards are revealed on the table. The starting player for each round changes clockwise. The round proceeds similarly to the first one.</p><p class='p4'><br></p><p class='p3'><span class='s1'>Third and Fourth Rounds:</span></p><p class='p4'><br></p><p class='p3'>At the beginning of each round, one card is discarded, and one is added to the middle of the table. By the fourth round, there should be five cards in the middle of the table. The rounds unfold similarly to the earlier rounds.</p><p class='p4'><br></p><p class='p3'><span class='s1'>The Showdown:</span></p><p class='p4'><br></p><p class='p3'>If only one player remains in the round (i.e., all other players have folded), that player collects the pot without revealing their hand. This feature allows for 'bluffing': a player can match or increase bets while holding a weak hand, hoping that players with stronger hands will fold.</p><p class='p3'>If more than one player remains after the final betting round, all hands are revealed, and the player with the winning hand claims the pot.</p><p class='p5'><span class='s2'></span><br></p></body></html>";

    tab1 -> setHtml(rules_of_poker);

    QString hands_in_poker = "<html><body>the hands of poker...</body></html>";
    tab2 -> setHtml(hands_in_poker) ;

    setStyleSheet("background-color:rgb(197, 220, 199);");
    setAutoFillBackground( true );

}

RulesWindow::~RulesWindow()
{
    delete ui;
}

void RulesWindow::CloseRulesWindow()
{
    this -> close() ;
}

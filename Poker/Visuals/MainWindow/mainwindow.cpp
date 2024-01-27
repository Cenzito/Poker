#include "mainwindow.hpp"
#include "Visuals/RulesWindow/ruleswindow.h"
#include "ui_mainwindow.h"
#include "../GameWindow/gamewindow.hpp"
#include "../Gamewindow/gamelocalwindow.hpp"
#include <Qcolor>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Apply stylesheets
    //ui->pushButton->setStyleSheet("background-color: #3498db; color: white;");
    //ui->pushButton_2->setStyleSheet("background-color: #3498db; color: white;");



    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onRulesButtonClicked);
    connect(ui->playlocal, &QPushButton::clicked, this, &MainWindow::on_playlocal_clicked);
    // Loading and setting the image to the QLabel
    //QPixmap image1("../Poker/Visuals/MainWindow/pokerpic.jpg");
    //ui->label->setPixmap(image1);

    //QLabel *imageLabel = new QLabel(this);
    //QPixmap imagePixmap(":/images/huge_player_stack.png");
    //if (imagePixmap.isNull()) {
    //    qDebug() << "Failed to load image";
    //}
    //QPixmap scaledPixmap = imagePixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //imageLabel->setPixmap(scaledPixmap);
    //imageLabel->resize(scaledPixmap.size());
    //imageLabel->move(400, 200);
    //imageLabel->setScaledContents(true); // Allow the pixmap to scale with the label
    //imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //QHBoxLayout *layout = new QHBoxLayout(this);
    //layout->addWidget(imageLabel);
    //imageLabel->resize(scaledPixmap.size());
    //this->setCentralWidget(centralWidget());



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlayButtonClicked()
{
    // Create and show the GameWindow when the PLAY button is clicked
    GameWindow *gameWindow = new GameWindow(this, "John");

    gameWindow->show();
}

void MainWindow::onRulesButtonClicked()
{
    RulesWindow *rulesWindow = new RulesWindow(this) ;
    rulesWindow->show();
}


void MainWindow::on_playlocal_clicked()
{
    GameLocalWindow *gamelocalwindow = new GameLocalWindow(this);

    Bot bot1 = Bot("bot1", 0);
    Bot bot2 = Bot("bot2", 0);

    gamelocalwindow->game.addBot(&bot1);
    gamelocalwindow->game.addBot(&bot2);

    gamelocalwindow -> show();
}

void MainWindow::on_pushButton_login_clicked()
{
    QString user = ui->lineEdit_user->text();
    QString pass = ui->lineEdit_pass->text();


}

void MainWindow::on_pushButton_signin_clicked()
{
    QString user = ui->lineEdit_newuser->text();
    QString pass = ui->lineEdit_newpass->text();

}


#include "mainwindow.hpp"
#include "Visuals/RulesWindow/ruleswindow.h"
#include "ui_mainwindow.h"
#include "../GameWindow/gamewindow.hpp"
#include "../Gamewindow/gamelocalwindow.hpp"
#include <Qcolor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Apply stylesheets
    //ui->pushButton->setStyleSheet("background-color: #3498db; color: white;");
    //ui->pushButton_2->setStyleSheet("background-color: #3498db; color: white;");



    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onRulesButtonClicked);
    //connect(ui->play_local, &QPushButton::clicked, this, &MainWindow::onLocalPlayButtonClicked);
    // Loading and setting the image to the QLabel
    //QPixmap image1("../Poker/Visuals/MainWindow/pokerpic.jpg");
    //ui->label->setPixmap(image1);

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

void MainWindow::onLocalPlayButtonClicked() {
    GameLocalWindow *gamelocalwindow = new GameLocalWindow(this);

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


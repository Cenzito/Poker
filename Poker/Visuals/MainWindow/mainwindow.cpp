#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "../GameWindow/gamewindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);

    // Loading and setting the image to the QLabel
    QPixmap image1("C:/Users/tamar/Desktop/Tamzi/faks/semester 3/cse201/poker project/Poker/Poker/Visuals/MainWindow/pokerpic.jpg"); //sorry for the longest adress ever
    ui->label_2->setPixmap(image1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlayButtonClicked()
{
    // Create and show the GameWindow when the PLAY button is clicked
    GameWindow *gameWindow = new GameWindow(this);
    gameWindow->show();
}


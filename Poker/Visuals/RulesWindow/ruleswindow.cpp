#include "ruleswindow.h"
#include "ui_ruleswindow.h"

RulesWindow::RulesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RulesWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &RulesWindow::CloseRulesWindow);

    setStyleSheet("background-color:darkseagreen;");
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

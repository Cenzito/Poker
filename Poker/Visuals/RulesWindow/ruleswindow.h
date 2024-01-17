#ifndef RULESWINDOW_H
#define RULESWINDOW_H

#include <QMainWindow>

#include <QVBoxLayout>
#include <QTabWidget>
#include <QTextBrowser>

namespace Ui {
class RulesWindow;
}

class RulesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RulesWindow(QWidget *parent = nullptr);
    ~RulesWindow();

private:
    Ui::RulesWindow *ui;
    QWidget* centralWidget;
    QVBoxLayout* layout;
    QTabWidget* tabWidget;
    QTextBrowser* tab1;
    QTextBrowser* tab2;

private slots:
    void CloseRulesWindow();

};

#endif // RULESWINDOW_H

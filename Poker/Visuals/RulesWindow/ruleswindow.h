#ifndef RULESWINDOW_H
#define RULESWINDOW_H

#include <QMainWindow>

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
};

#endif // RULESWINDOW_H

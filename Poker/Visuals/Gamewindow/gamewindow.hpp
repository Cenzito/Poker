#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    QString Get_image_path(std::string suit, std::string value, bool back = false); // to display the back call with args ("back", "back", true)

private slots:

    void on_dealButton_clicked();

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H

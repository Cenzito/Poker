#include "PokerPlayerLocal.hpp"



PokerPlayerLocal::PokerPlayerLocal(std::string name) : PokerPlayer(name)
{
}



int PokerPlayerLocal::Action() {

    //create buttons to choose bet size
    //QPushButton button("Click Me!", &window);
    //layout.addWidget(&button);

    // Create a timer
    QTimer timer;
    timer.setSingleShot(true); // Set the timer to fire only once

    // Create an event loop
    QEventLoop loop;

    // Connect the timer's timeout signal to the event loop's quit slot
    QObject::connect(&timer, &QTimer::timeout, [&loop]() {
        qDebug() << "false";
        loop.quit();
    });

    // Connect the button's clicked signal to the timer's start slot
    //QObject::connect(&button, &QPushButton::clicked, [&timer, &loop]() {
        //qDebug() << "true";
        //loop.quit();
    //});

    // Start the timer for 1000 milliseconds (1 second)
    timer.start(1000);

    // Run the event loop
    loop.exec();
}

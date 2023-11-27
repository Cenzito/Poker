QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bots/Easy/BotEasy.cpp \
    Bots/Medium/BotMedium.cpp \
    main.cpp \
    GameLogic/logic_scratch.cpp\
    Visuals/MainWindow/mainwindow.cpp


HEADERS += \
    Bots/Medium/BotMedium.hpp \
    GameLogic/logic_scratch.hpp\
    Visuals/MainWindow/mainwindow.h\
    Bots/Easy/BotEasy.hpp



FORMS += \
    Visuals/MainWindow/mainwindow.ui

RESOURCES = application.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

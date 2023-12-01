QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameLogic/PlayerInfo.cpp \
    Visuals/RulesWindow/rules.cpp \
    main.cpp \
    Bots/Bot.cpp \
    Bots/Easy/BotEasy.cpp \
    Bots/Easy/MonkeyBot.cpp \
    Bots/Easy/BotDrunk.cpp \
    Bots/Hard/Axel/BotAxel.cpp \
    Bots/Hard/Cenzo/BotCenzo.cpp \
    Bots/Hard/Darius/BotDarius.cpp \
    Bots/Hard/Kenza/BotKenza.cpp \
    Bots/Hard/Leal/BotLeal.cpp \
    Bots/Hard/Pu/BotPu.cpp \
    Bots/Medium/BotMedium.cpp \
    GameLogic/logic_scratch.cpp \
    GameLogic/PokerPlayer.cpp \
    GameLogic/Card.cpp \
    GameLogic/Deck.cpp \
    GameLogic/Table.cpp \
    GameLogic/Game.cpp \
    Visuals/Gamewindow/gamewindow.cpp \
    Visuals/MainWindow/mainwindow.cpp \

HEADERS += \
    Bots/Bot.hpp \
    Bots/Easy/BotDrunk.hpp \
    Bots/Easy/BotEasy.hpp \
    Bots/Easy/MonkeyBot.hpp \
    Bots/Hard/Axel/BotAxel.hpp \
    Bots/Hard/Cenzo/BotCenzo.hpp \
    Bots/Hard/Darius/BotDarius.hpp \
    Bots/Hard/Kenza/BotKenza.hpp \
    Bots/Hard/Leal/BotLeal.hpp \
    Bots/Hard/Pu/BotPu.hpp \
    Bots/Medium/BotMedium.hpp \
    GameLogic/PlayerInfo.hpp \
    GameLogic/PokerPlayer.hpp \
    GameLogic/logic_scratch.hpp \
    GameLogic/Card.hpp \
    GameLogic/Deck.hpp \
    GameLogic/Game.hpp \
    GameLogic/Table.hpp \
    Visuals/Gamewindow/gamewindow.hpp \
    Visuals/MainWindow/mainwindow.hpp \
    Visuals/RulesWindow/rules.hpp



FORMS += \
    Visuals/Gamewindow/gamewindow.ui \
    Visuals/MainWindow/mainwindow.ui



RESOURCES += \
    Visuals/Image.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

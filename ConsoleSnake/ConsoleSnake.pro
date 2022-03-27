TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /path/to/ncurses/headers/
LIBS += -L/path/to/ncurses/library/ -lncurses

HEADERS += \
        conio.h

SOURCES += \
        main.cpp

DISTFILES += \
  last_code.txt

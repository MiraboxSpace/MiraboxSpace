# websocket
QT += websockets

CONFIG += c++11

HEADERS += \
    $$PWD/Action.h \
    $$PWD/BasePlugin.h \
    $$PWD/ConnectionManager.h \
    $$PWD/CustomMain.h \
    $$PWD/Localizer.h \
    $$PWD/Logger.h \
    $$PWD/Plugin.h \
    $$PWD/SDKDefines.h

SOURCES += \
    $$PWD/Action.cpp \
    $$PWD/BasePlugin.cpp \
    $$PWD/ConnectionManager.cpp \
    $$PWD/CustomMain.cpp \
    $$PWD/Localizer.cpp \
    $$PWD/Logger.cpp \
    $$PWD/Plugin.cpp

INCLUDEPATH += $$PWD

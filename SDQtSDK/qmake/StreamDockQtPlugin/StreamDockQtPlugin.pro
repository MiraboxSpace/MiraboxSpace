QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 版本
VERSION = 1.0.0
# 版本号（VERSION_STR可以在代码中调用）
DEFINES += VERSION_STR=\\\"$$VERSION\\\"
# Static/compile-time major version of the Stream Dock.
DEFINES += SD_VERSION_MAJOR=1
# Static/compile-time minor version of the Stream Dock.
DEFINES += SD_VERSION_MINOR=0
# Static/compile-time patch version of the Stream Dock.
DEFINES += SD_VERSION_PATCH=0
# 目标文件名
TARGET = "StreamDockQtPlugin"
# 根据CONFIG选择DESTDIR的路径
CONFIG(debug, debug|release) {
    # DESTDIR（可执行文件存放的文件路径）
    DESTDIR = $$shell_path(./debug)
} else {
    # 以管理员身份运行
    #    QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
    # 屏蔽 QDebug
    # qDebug() QT_NO_DEBUG_OUTPUT
    # qWarning() QT_NO_WARNING_OUTPUT
    DEFINES += QT_NO_DEBUG_OUTPUT
    # 在Release模式下，也能输出文件信息，行数
    DEFINES += QT_MESSAGELOGCONTEXT
    # DESTDIR（可执行文件存放的文件路径）
    DESTDIR = $$shell_path(./release)
}
# MOC命令将含Q_OBJECT的头文件转换为标准的头文件寄存的目录
MOC_DIR = ./temp/moc
# RCC将qrc文件转化为头文件所寄存的目录
RCC_DIR = ./temp/rcc
# UIC将ui转化为头文件所寄存的目录
UI_DIR = ./temp/ui
# 指定所有中间文件.o（.obj）放置的目录。
OBJECTS_DIR = ./temp/obj

SOURCES += \
    ExampleAction.cpp \
    ExamplePlugin.cpp \
    main.cpp

HEADERS += \
    ExampleAction.h \
    ExamplePlugin.h

include(../../SDK/SDK.pri)

# Win
win32 {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

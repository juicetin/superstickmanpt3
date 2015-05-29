#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T19:48:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = INFO3220B1b
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    configreader.cpp \
    tinystickman.cpp \
    normalstickman.cpp \
    largestickman.cpp \
    giantstickman.cpp \
    background.cpp \
    stickmanfactory.cpp \
    obstacle.cpp \
    sprite.cpp \
    camera.cpp \
    level.cpp \
    stickmanadapter.cpp \
    stickman.cpp \
    subject.cpp \
    score.cpp \
    lives.cpp \
    game.cpp \
    inputhandler.cpp \
    pausecommand.cpp \
    quitcommand.cpp \
    jumpcommand.cpp \
    moveleftcommand.cpp \
    moverightcommand.cpp

HEADERS  += dialog.h \
    configreader.h \
    tinystickman.h \
    normalstickman.h \
    largestickman.h \
    giantstickman.h \
    background.h \
    stickmanfactory.h \
    obstacle.h \
    sprite.h \
    camera.h \
    level.h \
    stickmanadapter.h \
    stickman.h \
    observer.h \
    subject.h \
    score.h \
    lives.h \
    game.h \
    command.h \
    inputhandler.h \
    pausecommand.h \
    quitcommand.h \
    jumpcommand.h \
    moveleftcommand.h \
    moverightcommand.h

FORMS    += dialog.ui

RESOURCES += \
    gameresources.qrc

filestocopy.files = game.config \
  background.jpg
filestocopy.path = $$OUT_PWD

INSTALLS += filestocopy

CONFIG += c++11

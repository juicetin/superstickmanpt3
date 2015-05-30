#ifndef DIALOG_H
#define DIALOG_H

#define KEYPRESS 0
#define KEYRELEASE 1

#include "background.h"
#include "configreader.h"
#include "level.h"
#include "stickman.h"
#include "stickmanadapter.h"
#include "score.h"
#include "lives.h"
#include "game.h"
#include "inputhandler.h"

#include <QDialog>
#include <QKeyEvent>
#include <QTime>
#include <vector>
#include <ui_dialog.h>
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void nextFrame();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent *e);

private:
	Game *m_game;
	InputHandler *m_inputhandler;

    Ui::Dialog *ui;

    int m_timerMs;
    QTime m_time;


};

#endif // DIALOG_H

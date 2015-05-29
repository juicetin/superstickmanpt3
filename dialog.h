#ifndef DIALOG_H
#define DIALOG_H

#include "background.h"
#include "configreader.h"
#include "level.h"
#include "stickman.h"
#include "stickmanadapter.h"
#include "score.h"
#include "lives.h"
#include "game.h"

#include <QDialog>
#include <QKeyEvent>
#include <QTime>
#include <vector>

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
    Ui::Dialog *ui;

    // Reads from a configuration file and initialises the game.
    // Returns false if there are settings missing, in which case default values are used.

    int m_timerMs;
    QTime m_time;
};

#endif // DIALOG_H

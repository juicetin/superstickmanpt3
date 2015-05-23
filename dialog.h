#ifndef DIALOG_H
#define DIALOG_H

#include "background.h"
#include "configreader.h"
#include "level.h"
#include "stickman.h"
#include "stickmanadapter.h"
#include "score.h"
#include "lives.h"

#include <QDialog>
#include <QKeyEvent>
#include <QTime>

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

private:
    // Reads from a configuration file and initialises the game.
    // Returns false if there are settings missing, in which case default values are used.
    bool loadConfiguration(const ConfigReader &reader);

    Ui::Dialog *ui;
    int m_timerMs;
    Stickman *m_stickman;
    StickmanAdapter *m_stickmanAdapter;
    Background *m_background;
    bool m_paused;
    bool m_pauseScreenEnabled;
    bool m_stageThreeEnabled;
    QImage m_pauseImage;

    Level* m_level;

    Score m_score;
    Lives *m_lives;

    QTime m_time;
};

#endif // DIALOG_H

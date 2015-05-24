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
    // Reads from a configuration file and initialises the game.
    // Returns false if there are settings missing, in which case default values are used.
    bool loadConfiguration(const ConfigReader &reader);
    bool loadLevel(Level::Builder &levelBuilder, const ConfigReader &reader);

    Ui::Dialog *ui;
    int m_timerMs;
    Stickman *m_stickman;
    StickmanAdapter *m_stickmanAdapter;
    Background *m_background;

    bool m_paused;
    bool m_pauseScreenEnabled;
    bool m_stageThreeEnabled;
    bool m_moving;

    QImage m_pauseImage;

    Level* m_level;
    std::vector<std::string> m_levelConfigs;
    std::vector<std::string>::const_iterator m_levelConfigIterator;

    Score m_score;
    Lives *m_lives;

    QTime m_time;
};

#endif // DIALOG_H

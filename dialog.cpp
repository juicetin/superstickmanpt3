#include "dialog.h"

#include "camera.h"
#include "configreader.h"
#include "stickmanfactory.h"

#include <ui_dialog.h>
#include <QDir>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QStaticText>

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::Dialog),
m_game(NULL)

{
    ui->setupUi(this);
    m_game = new Game(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(20);
    m_time.restart();
}

Dialog::~Dialog()
{
	delete m_game;
    delete ui;
}

void Dialog::nextFrame()
{
    m_game->update(m_time);
    update();
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_game->render(painter);
}

void Dialog::keyPressEvent(QKeyEvent *e)
{
    if (m_game->m_pauseScreenEnabled &&
        !m_game->m_won &&
        !m_game->m_lost &&
        e->key() == Qt::Key_Escape)
    {
        m_game->m_paused = !m_game->m_paused;
    }

    if (e->key() == Qt::Key_Q)
    {
        this->close();
    }

    if (e->key() == Qt::Key_Space)
    {
        m_game->m_stickmanAdapter->jump();
    }

    if (m_game->m_stageThreeEnabled && e->key() == Qt::Key_Left)
    {
        m_game->m_stickmanAdapter->setXVelocity(-170);
        m_game->m_moving = true;
    }

    if (m_game->m_stageThreeEnabled && e->key() == Qt::Key_Right)
    {
        m_game->m_stickmanAdapter->setXVelocity(170);
        m_game->m_moving = true;
    }
}

void Dialog::keyReleaseEvent(QKeyEvent *e)
{
    if (m_game->m_stageThreeEnabled && (e->key() == Qt::Key_Left || e->key() == Qt::Key_Right))
    {
        m_game->m_stickmanAdapter->setXVelocity(0);
        m_game->m_moving = false;
    }
}

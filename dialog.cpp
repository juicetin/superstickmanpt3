#include "dialog.h"

Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::Dialog),
m_inputhandler(new InputHandler())
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
	delete m_inputhandler;
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
    Command *command = m_inputhandler->handleInput(e);
	if (command)
	{
         command->execute(m_game, this);
	}
}

void Dialog::keyReleaseEvent(QKeyEvent *e)
{
    if (m_game->stage3State() && (e->key() == Qt::Key_Left || e->key() == Qt::Key_Right))
    {
		m_game->getStickman()->stop();
		m_game->charNotMoving();
    }
}

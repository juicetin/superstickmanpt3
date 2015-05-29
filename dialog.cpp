#include "dialog.h"

#include "camera.h"
#include "configreader.h"
#include "stickmanfactory.h"

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
	InputHandler inputHandler;
	Command *command = inputHandler.handleInput(*e);
	if (command)
	{
		// command->execute(actor);
	}
    if (m_game->pauseEnabled() &&
        !m_game->wonState() &&
        !m_game->lostState() &&
        e->key() == Qt::Key_Escape)
    {
		m_game->switchPaused();
    }

    if (e->key() == Qt::Key_Q)
    {
        this->close();
    }

    if (e->key() == Qt::Key_Space)
    {
		m_game->getStickman()->jump();
    }

    if (m_game->stage3State() && e->key() == Qt::Key_Left)
    {
		m_game->getStickman()->moveLeft();
		m_game->charMoving();
    }

    if (m_game->stage3State() && e->key() == Qt::Key_Right)
    {
		m_game->getStickman()->moveRight();
		m_game->charMoving();
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

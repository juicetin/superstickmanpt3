#include "inputhandler.h"

InputHandler::InputHandler() {}

Command * InputHandler::handleInput(QKeyEvent *e)
{
    if (e->key == Qt::Key_Escape) return m_pause;
    if (e->key == Qt::Key_Q) 	  return m_quit;
    if (e->key == Qt::Key_Space)  return m_jump;
    if (e->key == Qt::Key_Left)	  return m_moveLeft;
    if (e->key == Qt::Key_Right)  return m_moveRight;

	//	Nothing is pressed
	return NULL;
}

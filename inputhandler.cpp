#include "inputhandler.h"

InputHandler::InputHandler() :
	key_p(),
	key_q(),
	key_space(),
	key_left(),
	key_right()
{}

Command * InputHandler::handleInput(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape) return key_p;
    if (e->key() == Qt::Key_Q)      return key_q;
    if (e->key() == Qt::Key_Space)  return key_space;
    if (e->key() == Qt::Key_Left)	return key_left;
    if (e->key() == Qt::Key_Right)  return key_right;

	//	Nothing is pressed
	return NULL;
}

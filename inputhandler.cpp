#include "inputhandler.h"

#include <iostream>
using namespace std;

InputHandler::InputHandler() :
	key_p(new PauseCommand()),
	key_q(new QuitCommand()),
	key_space(new JumpCommand()),
	key_left(new MoveLeftCommand()),
	key_right(new MoveRightCommand())
{}

InputHandler::~InputHandler()
{
	delete key_p;
	delete key_q;
	delete key_space;
	delete key_left;
	delete key_right;
}

Command * InputHandler::handleInput(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
    {
//        cout << e->type() << endl;
//        cout << e->key() << endl;
//        cout << e->modifiers() << endl;
//        cout << e->text().toStdString() << endl;
//        cout << e->count() << endl;
        return key_p;
    }
    if (e->key() == Qt::Key_Q)      return key_q;
    if (e->key() == Qt::Key_Space)  return key_space;
    if (e->key() == Qt::Key_Left)	return key_left;
    if (e->key() == Qt::Key_Right)  return key_right;

    //	Nothing/non-handled is/are pressed
	return NULL;
}

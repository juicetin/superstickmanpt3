#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <Qt>
#include <QKeyEvent>
#include "command.h"

class InputHandler
{
	public:
		InputHandler();
        Command *handleInput(QKeyEvent *e);
	private:
		// Commands
        Command *m_pause;
		Command *m_quit;
		Command *m_jump;
		Command *m_moveLeft;
		Command *m_moveRight;
};

#endif // INPUTHANDLER_H

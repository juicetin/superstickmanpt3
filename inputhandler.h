#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <Qt>
#include <QKeyEvent>
#include "command.h"
#include "pausecommand.h"
#include "quitcommand.h"
#include "jumpcommand.h"
#include "moveleftcommand.h"
#include "moverightcommand.h"

class InputHandler
{
	public:
		InputHandler();
		~InputHandler();
        Command *handleInput(QKeyEvent *e);
	private:
		// Commands
        Command *key_p;
		Command *key_q;
		Command *key_space;
		Command *key_left;
		Command *key_right;
};

#endif // INPUTHANDLER_H

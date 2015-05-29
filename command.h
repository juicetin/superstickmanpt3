#ifndef COMMAND_H
#define COMMAND_H

#include <QDialog>

#include "game.h"

class Command
{
public:
    virtual ~Command() {}
    virtual void execute(Game *game, QDialog *dialog) = 0;
};

#endif // COMMAND_H

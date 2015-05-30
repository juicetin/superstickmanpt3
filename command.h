#ifndef COMMAND_H
#define COMMAND_H

#define KEYPRESS 0
#define KEYRELEASE 1

#include <QDialog>

#include "game.h"

class Command
{
public:
    virtual ~Command() {}
    virtual void execute(int keyType, Game *game, QDialog *dialog) = 0;
};

#endif // COMMAND_H

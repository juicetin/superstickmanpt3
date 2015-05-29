#ifndef COMMAND_H
#define COMMAND_H

#include "game.h"

class Command
{
public:
    virtual ~Command() {}
    virtual void execute(Game *game) = 0;
};

#endif // COMMAND_H

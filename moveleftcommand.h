#ifndef MOVELEFTCOMMAND_H
#define MOVELEFTCOMMAND_H

#include "command.h"

class MoveLeftCommand : public Command
{
public:
    virtual void execute (int keyType, Game *game, QDialog *dialog);
};

#endif // MOVELEFTCOMMAND_H

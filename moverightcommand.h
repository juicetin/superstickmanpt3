#ifndef MOVERIGHTCOMMAND_H
#define MOVERIGHTCOMMAND_H

#include "command.h"

class MoveRightCommand : public Command
{
public:
    virtual void execute (int keyType, Game *game, QDialog *dialog);
};

#endif // MOVERIGHTCOMMAND_H

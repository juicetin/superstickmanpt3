#ifndef JUMPCOMMAND_H
#define JUMPCOMMAND_H

#include "command.h"

class JumpCommand : public Command
{
public:
    virtual void execute (Game *game, QDialog *dialog);
};

#endif // JUMPCOMMAND_H

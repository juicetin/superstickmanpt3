#ifndef QUITCOMMAND_H
#define QUITCOMMAND_H

#include "command.h"

class QuitCommand : public Command
{
public:
    virtual void execute (Game *game, QDialog *dialog);
};

#endif // QUITCOMMAND_H

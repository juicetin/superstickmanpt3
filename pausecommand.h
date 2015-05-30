#ifndef PAUSECOMMAND_H
#define PAUSECOMMAND_H

#include "command.h"

class PauseCommand : public Command
{
public:
    virtual void execute (int keyType, Game *game, QDialog *dialog);
};

#endif // PAUSECOMMAND_H

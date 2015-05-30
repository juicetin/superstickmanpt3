#include "moverightcommand.h"

void MoveRightCommand::execute (int keyType, Game *game, QDialog *dialog)
{
    if (game->stage3State() && keyType == KEYPRESS)
    {
        game->getStickman()->moveRight();
        game->charMoving();
    }
    else if (game->stage3State() && keyType == KEYRELEASE)
    {
        game->getStickman()->stop();
        game->charNotMoving();
    }
}

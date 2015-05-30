#include "moveleftcommand.h"

void MoveLeftCommand::execute (int keyType, Game *game, QDialog *dialog)
{
    if (game->stage3State() && keyType == KEYPRESS)
    {
        game->getStickman()->moveLeft();
        game->charMoving();
    }
    else if (game->stage3State() && keyType == KEYRELEASE)
    {
        game->getStickman()->stop();
        game->charNotMoving();
    }
}

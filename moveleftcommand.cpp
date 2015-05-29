#include "moveleftcommand.h"

void MoveLeftCommand::execute (Game *game, QDialog *dialog)
{
    if (game->stage3State())
    {
        game->getStickman()->moveLeft();
        game->charMoving();
    }
}

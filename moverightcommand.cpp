#include "moverightcommand.h"

void MoveRightCommand::execute (Game *game, QDialog *dialog)
{
    if (game->stage3State())
    {
        game->getStickman()->moveRight();
        game->charMoving();
    }
}

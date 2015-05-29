#include "jumpcommand.h"

void JumpCommand::execute (Game *game, QDialog *dialog)
{
    game->getStickman()->jump();
}

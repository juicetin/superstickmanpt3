#include "jumpcommand.h"

void JumpCommand::execute (int keyType, Game *game, QDialog *dialog)
{
    game->getStickman()->jump();
}

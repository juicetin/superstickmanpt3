#include "jumpcommand.h"
#include <QSound>

void JumpCommand::execute (int keyType, Game *game, QDialog *dialog)
{
    if (game->getStickman()->jump() && game->jumpAllowed())
    {
        QSound::play(":/resources/jump.wav");
    }
}

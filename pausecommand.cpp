#include "pausecommand.h"

void PauseCommand::execute (int keyType, Game *game, QDialog *dialog)
{
    if (keyType == KEYPRESS && game->pauseEnabled() &&
            !game->wonState() && !game->lostState())
    {
        game->switchPaused();
    }
}

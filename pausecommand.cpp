#include "pausecommand.h"

void PauseCommand::execute (int keyType, Game *game, QDialog *dialog)
{
    if (game->pauseEnabled() && !game->wonState() &&
            !game->lostState())
    {
        game->switchPaused();
    }
}

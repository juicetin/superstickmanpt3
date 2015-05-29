#include "pausecommand.h"

void PauseCommand::execute (Game *game, QDialog *dialog)
{
    if (game->pauseEnabled() && !game->wonState() &&
            !game->lostState())
    {
        game->switchPaused();
    }
}

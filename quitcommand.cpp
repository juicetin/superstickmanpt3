#include "quitcommand.h"

void QuitCommand::execute (Game *game, QDialog *dialog)
{
    dialog->close();
}

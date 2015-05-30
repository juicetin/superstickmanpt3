#include "quitcommand.h"

void QuitCommand::execute (int keyType, Game *game, QDialog *dialog)
{
    dialog->close();
}

#include "dialog.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set current working directory to the app path so we can use
    // relative paths for the configuration file
    //QDir::setCurrent(QCoreApplication::applicationDirPath());

    Dialog w;
    w.show();

    return a.exec();
}

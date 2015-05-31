#include "dialog.h"

#include "tests.h"

#include <QApplication>
#include <QDir>
#include <cstring>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// Tests - always run these during development as you will
	// know if any changes broke anything. Remove for final release
	Dialog tmp;
	Tests tests(&tmp);
	tests.runAllTests();

    // Set current working directory to the app path so we can use
    // relative paths for the configuration file
    //QDir::setCurrent(QCoreApplication::applicationDirPath());

	Dialog w;
	w.show();

	return a.exec();
}

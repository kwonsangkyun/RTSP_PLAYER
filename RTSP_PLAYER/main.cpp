#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMainWindow w;
	int exitCode = -1;

	if (w.initialize() == true)
	{
		w.show();
		exitCode = a.exec();
		w.uninitialize();
	}

	return true;
}

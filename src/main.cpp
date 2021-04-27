#include "dialog.h"
#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Logger::initialize();

	Dialog w;
	w.show();

	// cleanup before quit
	QObject::connect(&a, &QApplication::aboutToQuit, []{
		Logger::terminate();
	});

	return a.exec();
}

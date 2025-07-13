#include <QCoreApplication>
#include "PluginDaemon.h"

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	PluginDaemon daemon("MyPluginSocket");
	return app.exec();
}

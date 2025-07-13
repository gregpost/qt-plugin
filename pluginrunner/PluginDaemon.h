#include <QCoreApplication>       // for app dir path
#include <QPluginLoader>          // to load/unload plugins at runtime
#include <QScopedPointer>         // RAII wrapper for plugin logic
#include <QLocalSocket>           // IPC: local socket client
#include <QLocalServer>           // IPC: local socket server
#include <QFileSystemWatcher>     // watch plugin file for rebuild
#include "QTimer"                 // for delayed plugin reload
#include "PluginInterface.h"      // base interface for the plugin

class PluginDaemon : public QObject {
    Q_OBJECT
public:
    PluginDaemon(const QString& socketName, QObject* parent = nullptr)
        : QObject(parent), server(new QLocalServer(this))
    {
        // start server and wait for connections
        server->listen(socketName);
        connect(server, &QLocalServer::newConnection,
                this, &PluginDaemon::handleClient);

        // load plugin for the first time
        loadPlugin();

        // watch plugin file for changes (e.g. rebuild)
        watcher.addPath(pluginPath);
        connect(&watcher, &QFileSystemWatcher::fileChanged,
                this, &PluginDaemon::reloadPlugin);
    }

private slots:
    void handleClient() {
        auto client = server->nextPendingConnection();

        connect(client, &QLocalSocket::readyRead, [this, client]() {
            QByteArray req = client->readAll();

            // crude parser: expects an int as raw string
            int x = parse(req);

            // call plugin logic
            int result = logic->compute(x);

            // send result back
            client->write(QByteArray::number(result));
            client->flush();
            client->disconnectFromServer();
        });
    }

    void loadPlugin() {
        // unload if already loaded
        if (loader.isLoaded()) loader.unload();

        loader.setFileName(pluginPath);
        loader.load();

        // get plugin instance, cast it to our interface
        auto factory = qobject_cast<PluginInterface*>(loader.instance());
        logic.reset(factory ? factory->createLogic() : nullptr);
    }

    void reloadPlugin() {
        // small delay so build can finish writing the file
        QTimer::singleShot(200, this, &PluginDaemon::loadPlugin);

        // need to re-add the file because QFileSystemWatcher only fires once
        watcher.addPath(pluginPath);
    }

private:
    QString pluginPath = QCoreApplication::applicationDirPath() + "/myplugin.dll";
    QPluginLoader loader;
    QScopedPointer<PluginLogic> logic;
    QLocalServer* server;
    QFileSystemWatcher watcher;

    int parse(const QByteArray& input) {
        // very basic int parser
        bool ok = false;
        int value = input.trimmed().toInt(&ok);
        return ok ? value : 0;
    }
};

#include "PluginInterface.h"
#include <QObject>

// Actual logic implementation that will be used by the daemon
class MyPluginLogic : public PluginLogic {
    Q_OBJECT
public:
    // Plugin name — can be used for logging, UI, or diagnostics
    QString pluginName() const override {
        return "MyPlugin: Hello from DLL!";
    }

    // Core logic exposed by the plugin — customize as needed
    int compute(int x) override {
        return x * 10;  // simple example logic
    }
};

// Factory class that exposes plugin interface for dynamic loading
class MyPlugin : public QObject, public PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_iid)  // Required for Qt plugin system
    Q_INTERFACES(PluginInterface)               // Tells Qt this implements PluginInterface

public:
    // Called by the host app to get an instance of logic
    PluginLogic* createLogic(QObject* parent = nullptr) override {
        return new MyPluginLogic();  // ownership passed to caller
    }
};

#include "MyPlugin.moc"  // Required if using Q_OBJECT in headerless class

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <QString>

class PluginLogic : public QObject {
    Q_OBJECT
public:
    virtual QString pluginName() const = 0;
    virtual ~PluginLogic() = default;
    virtual int compute(int x) = 0;
};

class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual PluginLogic* createLogic(QObject* parent = nullptr) = 0;
};

#define PluginInterface_iid "org.example.PluginInterface/1.0"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

#endif

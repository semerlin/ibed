#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "framework_global.h"
#include "iappmodule.h"
#include <QList>
#include <QHash>
#include <QStringList>

class FRAMEWORKSHARED_EXPORT ModuleManager : public QObject
{
    Q_OBJECT

public:
    typedef enum
    {
        MODULE_ADD,
        MODULE_REMOVE,
        MODULE_LOADING,
        MODULE_LOADED,
        MODULE_LOAD_FAILED,
        MODULE_UNLOADING,
        MODULE_UNLOADED,
        MODULE_UNLOAD_FAILED,
        MODULE_UNLOAD,
        MODULE_RELOADING,
        MODULE_RELOADED,
        MODULE_RELOAD_FAILED,
        MODULE_LOAD_FINISHED,
        MODULE_RELOAD_FINISHED,
    }MODULE_STATUS;

public:
    ModuleManager();
    ~ModuleManager();

public:
    /**
     * @brief add module
     * @param module
     */
    void addModule(IAppModule *module);

    /**
     * @brief add modules
     * @param modules
     */
    void addModules(const QList<IAppModule *> &modules);

    /**
     * @brief set modules
     * @param modules
     */
    void setModules(const QList<IAppModule *> &modules);

    /**
     * @brief remove a module
     * @param module: module pointer
     */
    void removeModule(IAppModule *module);

    /**
     * @brief remove a module by name
     * @param name: module name
     */
    void removeModule(const QString &name);

    /**
     * @brief return all modules
     * @return
     */
    QList<IAppModule *> modules(void) const;

    /**
     * @brief return module with given name
     * @param name: module name
     * @return
     */
    IAppModule* module(const QString &name);

    template <typename T>
    T *moduleConvert(const QString &name);
    /**
     * @brief return all module names
     * @return
     */
    QStringList moduleNames(void) const;

    /**
     * @brief loaded modules
     * @return
     */
    QList<IAppModule *> loadedModules(void) const;

    /**
     * @brief loaded module names
     * @return
     */
    QStringList loadedModuleNames(void) const;

    /**
     * @brief unloaded modules
     * @return
     */
    QList<IAppModule *> unloadedModules(void) const;

    /**
     * @brief unloaded module names
     * @return
     */
    QStringList unloadedModuleNames(void) const;

    /**
     * @brief load one module by name, if this module is already loaded,
     *        nothing will do
     * @param name: module name
     * @return true: success
     *         false: failed
     */
    bool loadModule(const QString &name, const QVariant &val = QVariant(QVariant::Invalid));

    /**
     * @brief load all modules
     * @return
     */
    bool loadModules(const QVariant &val = QVariant::Invalid);

    /**
     * @brief reload module, if this module is already loaded,
     *        it will unload it first then load it
     * @param name: module name
     * @return true: success
     *         false: failed
     */
    bool reloadModule(const QString &name, const QVariant &val = QVariant(QVariant::Invalid));

    /**
     * @brief reload all modules
     * @return
     */
    bool reloadModules(const QVariant &val);

    /**
     * @brief unload a module by name, if this module has not been loaded,
     *        nothing will do
     */
    void unloadModule(const QString &name);

    /**
     * @brief unload all modules
     */
    void unloadModules(void);

    /**
     * @brief set flag to true if ModuleManger run
     *        out of main thread
     * @param
     */
    void setOutMainThread(bool flag);

    /**
     * @brief return true if ModuleManger run out of
     *        main thread
     * @return
     */
    bool isOutMainThread(void) const;

    /**
     * @brief error message if any error happens
     * @return
     */
    QString error(void) const;

public:
    /**
     * @brief invoke this function to emit moduleChanged signal;
     * @param
     * @param
     */
    void moduleChanging(IAppModule *module, ModuleManager::MODULE_STATUS status);

signals:
    void moduleChanged(IAppModule *module, ModuleManager::MODULE_STATUS status);

private slots:
    void onLoadModule(const QString &name, const QVariant &val);
    void onLoadModules(const QVariant &val);
    void onModuleDestroyed(QObject *module);

private:
    QList<IAppModule *> m_modules;
    QHash<QString, IAppModule *> m_moduleWithNames;
    QString m_error;
    bool m_isOutMainThread;
};


template <typename T>
T* ModuleManager::moduleConvert(const QString &name)
{
    if(m_moduleWithNames.contains(name))
    {
        return dynamic_cast<T *>(m_moduleWithNames[name]);
    }
    else
        return NULL;
}



#endif // MODULEMANGER_H

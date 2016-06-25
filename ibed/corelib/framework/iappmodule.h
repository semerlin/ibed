#ifndef IAPPMODULE_H
#define IAPPMODULE_H

#include "framework_global.h"
#include <QVariant>

class FRAMEWORKSHARED_EXPORT IAppModule : public QObject
{
    Q_OBJECT
public:
    IAppModule() {}
    virtual ~IAppModule() {}

public:
    /**
     * @brief load this module
     * @param val: value pass in this module
     * @return true: load success
     *         false: load failed
     */
    virtual bool load(const QVariant &val = QVariant(QVariant::Invalid)) = 0;

    /**
     * @brief is this module has already beenl loaded?
     * @return true: yes
     *         false: no
     */
    virtual bool isLoaded(void) const = 0;

    /**
     * @brief unload this module
     */
    virtual void unload(void) = 0;

    /**
     * @brief reload this module
     */
    virtual void reload(void) = 0;

    /**
     * @brief set module name
     * @param name: module name
     */
    virtual void setName(const QString &name) = 0;
    /**
     * @brief module name
     * @return module name
     */
    virtual QString name(void) const = 0;

    /**
     * @brief error string if load failed
     * @return error string
     */
    virtual QString error(void) const = 0;

    /**
     * @brief is this module can run in thread that
     *        is not the main thread
     */
    virtual bool canRunInThread(void) const  = 0;

signals:
    void message(const QString &msg);
};

#endif // IAPPMODULE


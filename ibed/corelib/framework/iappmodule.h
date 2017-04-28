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
     * @param val - value pass to this module
     * @return load status
     */
    virtual bool load(const QVariant &val = QVariant(QVariant::Invalid)) = 0;

    /**
     * @brief is this module has already been loaded?
     * @return true -  yes
     *         false -  no
     */
    virtual bool isLoaded(void) const = 0;

    /**
     * @brief unload this module
     */
    virtual void unload(void) = 0;

    /**
     * @brief reload this module
     * @return reload status
     */
    virtual bool reload(void) = 0;

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
     * @brief error code if load failed
     * @return error code
     */
    virtual QString error(void) const = 0;

signals:
    void message(const QString &msg);
};

#endif // IAPPMODULE


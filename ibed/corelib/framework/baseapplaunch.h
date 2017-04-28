#ifndef BASEAPPLAUNCH_H
#define BASEAPPLAUNCH_H

#include "framework_global.h"
#include "iapplaunch.h"
#include <QObject>

class BaseAppLaunchPrivate;
class IAppLaunchWidget;
class ModuleManager;

/**
 * @brief base application lanch framework
 */
class FRAMEWORKSHARED_EXPORT BaseAppLaunch : public QObject, public IAppLaunch
{
    Q_OBJECT
public:
    explicit BaseAppLaunch(IAppLaunchWidget *parent, ModuleManager *manager);
    virtual ~BaseAppLaunch();

public:
    /**
     * @brief start launch application
     * @param argc
     * @param argv
     * @return
     */
    virtual int run(int argc, char **argv);

signals:
    /**
     * @brief this signal will emit when launch finished
     */
    void launchFinished();

private:
    BaseAppLaunchPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(BaseAppLaunch)
};

#endif // BASEAPPLANCHER_H

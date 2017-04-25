#ifndef BASEAPPLAUNCH_H
#define BASEAPPLAUNCH_H

#include "framework_global.h"
#include "iapplaunch.h"
#include "modulemanager.h"
#include "iapplaunchwidget.h"

/**
 * @brief base application lanch framework
 */
class FRAMEWORKSHARED_EXPORT BaseAppLaunch : public QObject, public IAppLaunch
{
    Q_OBJECT
public:
    explicit BaseAppLaunch(IAppLaunchWidget *parent, ModuleManager *manger);
    virtual ~BaseAppLaunch();

public:
    virtual int run(int argc, char **argv);

private slots:
    void onModuleChanged(IAppModule *module, ModuleManager::MODULE_STATUS status);
    void onStartLaunch();

signals:
    void startLaunch(const QVariant &val);
    void launchFinished();

private:
    IAppLaunchWidget *m_widget;
    ModuleManager *m_moduleManger;
    QVariant m_extVal;
};

#endif // BASEAPPLANCHER_H

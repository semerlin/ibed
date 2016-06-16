#ifndef BASEAPPLAUNCH_H
#define BASEAPPLAUNCH_H

#include "framework_global.h"
#include "iapplaunch.h"
#include "modulemanger.h"
#include "iapplaunchwidget.h"

/**
 * @brief base application lanch framework
 */
class FRAMEWORKSHARED_EXPORT BaseAppLaunch : public QObject, public IAppLaunch
{
    Q_OBJECT
public:
    explicit BaseAppLaunch(IAppLaunchWidget *parent, ModuleManger *manger);
    virtual ~BaseAppLaunch();

public:
    virtual int run(int argc, char **argv);
    virtual int restart(void);

private slots:
    void onModuleChanged(IAppModule *module, ModuleManger::MODULE_STATUS status);

signals:
    void startLaunch(const QVariant &val);

private:
    IAppLaunchWidget *m_widget;
    ModuleManger *m_moduleManger;
    QThread *m_thread;
};

#endif // BASEAPPLANCHER_H
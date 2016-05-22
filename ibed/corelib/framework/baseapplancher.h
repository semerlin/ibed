#ifndef BASEAPPLANCHER_H
#define BASEAPPLANCHER_H

#include "framework_global.h"
#include "iapplancher.h"
#include "modulemanger.h"
#include "iapplancherwidget.h"

/**
 * @brief base application lanch framework
 */
class FRAMEWORKSHARED_EXPORT BaseAppLancher : public QObject, public IAppLancher
{
    Q_OBJECT
public:
    explicit BaseAppLancher(IAppLancherWidget *parent, ModuleManger *manger);
    virtual ~BaseAppLancher();

public:
    virtual int run(int argc, char **argv);
    virtual int restart(void);

private slots:
    void onModuleChanged(IAppModule *module, ModuleManger::MODULE_STATUS status);

signals:
    void startLanch(const QVariant &val);

private:
    IAppLancherWidget *m_widget;
    ModuleManger *m_moduleManger;
    QThread *m_thread;
};

#endif // BASEAPPLANCHER_H

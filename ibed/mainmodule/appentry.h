#ifndef APPENTRY_H
#define APPENTRY_H

#include "mainmodule_global.h"
#include "launchwidget.h"
#include "modulemanger.h"

class MAINMODULESHARED_EXPORT AppEntry : public QObject
{
    Q_OBJECT

public:
    static AppEntry &instance();

public:
    int run(int argc, char **argv);

private slots:
    void onLaunchFinished(void);

private:
    LaunchWidget *m_widget;
    ModuleManger *m_manger;


private:
    AppEntry();

};

#endif // APPENTRY_H

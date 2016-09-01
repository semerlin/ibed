#ifndef APPENTRY_H
#define APPENTRY_H

#include "mainmodule_global.h"
#include <QObject>

class LaunchWidget;
class MainModule;

class MAINMODULESHARED_EXPORT AppEntry : public QObject
{
    Q_OBJECT

public:
    static AppEntry &instance();

public:
    int run(int argc, char **argv);

private slots:
    void onLaunchFinished(void);
    void onMainWidgetShown(void);

private:
    LaunchWidget *m_widget;
    MainModule *m_mainModule;

private:
    AppEntry();
    ~AppEntry();

};

#endif // APPENTRY_H

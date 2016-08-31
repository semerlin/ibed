#ifndef MAINMODULE_H
#define MAINMODULE_H

#include "mainmodule_global.h"
#include <QObject>

class ModuleManger;

class MAINMODULESHARED_EXPORT MainModule : public QObject
{
    Q_OBJECT

public:
    MainModule();

public:
    bool initialize(void);
    ModuleManger *manger(void) const;

signals:
    void play(const QString &name);

private slots:
    void onBedControlPressed(int id);
    void onBedControlReleased(int id);
    void onInfuStart(void);
    void onInfuStop(void);
    void onInfuInputChanged(int input);
    void onCallOutConnecting(void);
    void onCallOutConnected(void);
    void onCallOutTerminate(void);

private:
    ModuleManger *m_manger;
};

#endif // MAINMODULE_H

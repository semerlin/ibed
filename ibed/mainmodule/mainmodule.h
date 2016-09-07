#ifndef MAINMODULE_H
#define MAINMODULE_H

#include "mainmodule_global.h"
#include <QObject>
#include <QMap>

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
    void onMotorMove(const QMap<quint8, quint8> &moves);


private:
    ModuleManger *m_manger;
};

#endif // MAINMODULE_H

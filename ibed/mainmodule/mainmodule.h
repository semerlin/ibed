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

private slots:
    void onBedControlPressed(int id);
    void onBedControlReleased(int id);
    void onInfuStart(void);
    void onInfuStop(void);
    void onInfuInputChanged(int input);
//    void onCallOutConnecting(void);
//    void onCallInConnecting(void);
//    void onCallConnected(void);
    void onCallTerminate(void);
    void onMotorMove(const QMap<quint8, quint8> &moves);
    void prepareCall(void);

private slots:
    void callOutTimer(void);

private:
    ModuleManger *m_manger;
};

#endif // MAINMODULE_H

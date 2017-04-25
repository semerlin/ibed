#ifndef MAINMODULE_H
#define MAINMODULE_H

#include "mainmodule_global.h"
#include <QObject>
#include <QMap>

class ModuleManager;

class MAINMODULESHARED_EXPORT MainModule : public QObject
{
    Q_OBJECT

public:
    MainModule();

public:
    bool initialize(void);
    ModuleManager *manger(void) const;

private slots:
    void onBedControlPressed(int id);
    void onBedControlReleased(int id);
    void onInfuStart(void);
    void onInfuStop(void);
    void onInfuInputChanged(int input);
    void onCallTerminate(void);
    void onMotorMove(const QMap<quint8, quint8> &moves);
    void prepareCall(void);

private slots:
    void callOutTimer(void);

private:
    ModuleManager *m_manager;
};

#endif // MAINMODULE_H

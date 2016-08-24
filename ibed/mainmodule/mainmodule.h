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

private slots:
    void onBedControlPressed(int id);
    void onBedControlReleased(int id);

private:
    ModuleManger *m_manger;
};

#endif // MAINMODULE_H

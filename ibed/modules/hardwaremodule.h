#ifndef HARDWAREMODULE_H
#define HARDWAREMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class MODULESSHARED_EXPORT HardwareModule : public BaseAppModule
{
    Q_OBJECT
public:
    HardwareModule(const QString &name);
    ~HardwareModule();

public:
    bool load(const QVariant &val);
    void unload();

public slots:
    void backlightOn(void);
    void setBrightness(int value);
    void setTurnOffTime(int value);

};

#endif // HARDWAREMODULE_H

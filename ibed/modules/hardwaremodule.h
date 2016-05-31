#ifndef HARDWAREMODULE_H
#define HARDWAREMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class MODULESSHARED_EXPORT HardwareModule : public BaseAppModule
{
public:
    static HardwareModule &instance(void);

public:
    bool load(const QVariant &val);
    void unload();

public:


private:
    HardwareModule(const QString &name);
};

#endif // HARDWAREMODULE_H

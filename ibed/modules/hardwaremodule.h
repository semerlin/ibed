#ifndef HARDWAREMODULE_H
#define HARDWAREMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class MODULESSHARED_EXPORT HardwareModule : public BaseAppModule
{
public:
    HardwareModule(const QString &name);
    ~HardwareModule();

public:
    bool load(const QVariant &val);
    void unload();

};

#endif // HARDWAREMODULE_H

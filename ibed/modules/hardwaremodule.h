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

private:
    HardwareModule(const QString &name);
    ~HardwareModule();
};

#endif // HARDWAREMODULE_H

#ifndef IPOWERMANGEDEVICE_H
  #define IPOWERMANGEDEVICE_H

#include <QObject>
#include "hardware_global.h"
#include "powerdef.h"


class PowerMange;

/**
 * @brief devices need power mangement must inherit this class
 */
class HARDWARESHARED_EXPORT IPowerMangeDevice
{
public:
    IPowerMangeDevice();
    virtual ~IPowerMangeDevice();

public:
    virtual QString deviceName(void) const
    {
        return "Unkonwn";
    }

protected:
    virtual void EnterState(POWER_STATE state) = 0;

private:
    friend class PowerMange;
};

#endif // IPOWERMANGEDEVICE


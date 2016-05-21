#ifndef IDEVICE_H
  #define IDEVICE_H


#include "hardware_global.h"
#include <QObject>
#include "powerdef.h"


/**
 * @brief hardware device interface
 */
class HARDWARESHARED_EXPORT IDevice : public QObject
{
public:
    virtual ~IDevice() {}

public:
    virtual QString name(void) const = 0;
    virtual void EnterState(POWER_STATE state) = 0;
    virtual bool isReadable(void) const = 0;
    virtual bool isWriteable(void) const = 0;
    virtual bool isReadonly(void) const = 0;
};

#endif // IDEVICE_H


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
    /**
     * @brief return device name
     * @return
     */
    virtual QString name(void) const = 0;

    /**
     * @brief control device state
     * @param state
     */
    virtual void EnterState(POWER_STATE state) = 0;

    /**
     * @brief isReadable
     * @return
     */
    virtual bool isReadable(void) const = 0;

    /**
     * @brief isWriteable
     * @return
     */
    virtual bool isWriteable(void) const = 0;

    /**
     * @brief isReadonly
     * @return
     */
    virtual bool isReadonly(void) const = 0;
};

#endif // IDEVICE_H


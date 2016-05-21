#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include "hardware_global.h"
#include "idevice.h"

class HARDWARESHARED_EXPORT Backlight : public IDevice
{
    Q_OBJECT

public:
    virtual ~Backlight() {}

public:
    static Backlight &instance(void);
    QString deviceName() const;

public:
    QString name() const;
    virtual void EnterState(POWER_STATE state);
    bool isReadable() const;
    bool isWriteable() const;
    bool isReadonly() const;
    quint8 value(void);
    quint8 maxValue(void);


public slots:
    void setValue(quint8 newValue);

signals:
    void brightnessChanged(quint8 prev, quint8 current);

private:
    Backlight();
    void autoSetValue(quint8 value);

private:
    quint8 m_curVal;
};

#endif // BACKLIGHT_H

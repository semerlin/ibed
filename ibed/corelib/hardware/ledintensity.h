#ifndef LEDINTENSITY_H
#define LEDINTENSITY_H


#include "hardware_global.h"
#include "idevice.h"

class HARDWARESHARED_EXPORT LedIntensity : public IDevice
{
    Q_OBJECT

public:
    virtual ~LedIntensity() {}

public:
    static LedIntensity &instance(void);
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
    LedIntensity();
    void autoSetValue(quint8 value);

private:
    quint8 m_onVal;
    quint8 m_prevVal;
};

#endif // LEDINTENSITY_H

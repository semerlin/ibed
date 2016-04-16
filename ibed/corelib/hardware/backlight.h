#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include "hardware_global.h"
#include <QObject>


class HARDWARESHARED_EXPORT Backlight : public QObject
{
    Q_OBJECT
public:
    static Backlight &instance(void);

public slots:
    void setValue(quint8 newValue);
    void setTurnOffTime(qint32 newTime);

public:
    quint8 value(void);
    quint8 maxValue(void);

signals:
    void valueChanged(quint8 value);
    void turnOffTimeChanged(qint32 time);

private:
    Backlight();

private:
    quint8 m_prevVal;
};

#endif // BACKLIGHT_H

#ifndef HARDWAREMODULE_H
#define HARDWAREMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class QTimer;

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

signals:
    void lightIntensityChanged(int intensity);
    void temperatureChanged(int temper);
    void humidityChanged(int humidity);

private slots:
    void updateLightIntensity(void);
    void updateTemper(void);

private:
    QTimer *m_lightTimer;
    QTimer *m_temperTimer;
    int m_lightIntensity;
    int m_temper;
    int m_humidity;

private:
    void loadDrivers(void);

};

#endif // HARDWAREMODULE_H

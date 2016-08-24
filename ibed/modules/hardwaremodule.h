#ifndef HARDWAREMODULE_H
#define HARDWAREMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class QTimer;
class SHT20;

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
    void motorMove(int id, int dir);
    void startInfusion(void);
    void stopInfusion(void);

signals:
    void lightIntensityChanged(int intensity);
    void temperatureChanged(int temper);
    void humidityChanged(int humidity);
    void infuCountChanged(int count);
    void infuSpeedChanged(int speed);
    void infuMountChanged(int mount);
    void weightChanged(double weight);

private slots:
    void updateLightIntensity(void);
    void updateTemper(void);
    void updateInfusion(void);
    void updateWeight(void);

private:
    QTimer *m_lightTimer;
    QTimer *m_temperTimer;
    int m_lightIntensity;
    int m_temper;
    int m_humidity;
    SHT20 *m_sht20;
    QTimer *m_infuTimer;
    QTimer *m_weightTimer;

private:
    void loadDrivers(void);

};

#endif // HARDWAREMODULE_H

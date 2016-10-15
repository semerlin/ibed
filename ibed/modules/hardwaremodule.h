#ifndef HARDWAREMODULE_H
#define HARDWAREMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"
#include <QPair>

class QTimer;
class SHT20;
class KeyboardMange;
class QMutex;

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
    void motorMove(const QMap<quint8, quint8> &moves);
    void startInfusion(void);
    void stopInfusion(void);

signals:
    void lightIntensityChanged(int intensity);
    void temperatureChanged(int temper);
    void humidityChanged(int humidity);
    void infuSpeedChanged(int speed);
    void infuInputChanged(int input);
    void weightChanged(double weight);
    void callPressed(void);
    void cancelPressed(void);

private slots:
    void updateLightIntensity(void);
    void updateTemper(void);
    void updateInfusion(void);
    void updateWeight(void);
    void onKeyStatusChanged(void);
    void onInfuCountChanged(int count);

private:
    QTimer *m_lightTimer;
    QTimer *m_temperTimer;
    int m_lightIntensity;
    int m_temper;
    int m_humidity;
    SHT20 *m_sht20;
    QTimer *m_infuTimer;
    QTimer *m_weightTimer;
    KeyboardMange *m_kbdMange;
    QMutex *m_i2cMutex;
    int m_infuMount;
    bool m_firstInfu;
    int m_prevCount;
    int m_infuCount;

private:
    void loadDrivers(void);

};

#endif // HARDWAREMODULE_H

#ifndef UIMODULE_H
#define UIMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"


class MainWidget;
class StandbyWidget;
class CallDialog;
class ProgressDialog;
class NumIPMethod;
class QTimer;

class MODULESSHARED_EXPORT UiModule : public BaseAppModule
{
    Q_OBJECT

public:
    UiModule(const QString &name);
    ~UiModule();

public:
    bool load(const QVariant &val);
    void unload();

public:
    void showMainWidget();
    int infuMount(void) const;

signals:
    void reconnect(const QString &ip, quint16 port, quint16 device,
           const QString &localIp, const QString localMask, const QString localGateway);
    void updateAdvise();
    void uploadInOut(const QStringList &data);
    void brightnessChanged(int value);
    void turnOffTimeChanged(int value);
    void play(const QString &name);
    void pause(const QString &name);
    void stop(const QString &name);
    void bedCtrlPressed(int id);
    void bedCtrlReleased(int id);
    void infuStart(void);
    void infuStop(void);

private slots:
    void onRegistered();
    void onRegisterTimeout();
    void onDisconnect();
    void onNameChanged(const QString &name);
    void onSexChanged(const QString &sex);
    void onAgeChanged(const QString &age);
    void onBedChanged(const QString &bed);
    void onLevelChanged(const QString &level);
    void onTimeChanged(const QString &time);
    void onDoctorChanged(const QString &doctor);
    void onEatChanged(const QString &eat);
    void onNurseChanged(const QString &nurse);
    void onAdviseChanged(const QString &advise);
    void onAllergyChanged(const QString &allergy);
    void onAdviseUpdate(const QString &data);
    void onStandbyTimeout();
    void onStandbyClicked();
    void onLightIntensityChanged(int intensity);
    void onTemperatureChanged(int temper);
    void onHumidityChanged(int humidity);
    void onAudioIntensityChanged(int intensity);
    void onClicked(void);
    void onWeightChanged(double weight);
    void onInfuInputChanged(int mount);
    void onInfuSpeedChanged(int speed);
    void onCallOutConnecting(void);
    void onCallOutConnected(void);
    void onCallOutTerminate(void);
    void onBedCtrlPressed(void);
    void onBedCtrlReleased(void);

private:
    MainWidget *m_mainWidget;
    StandbyWidget *m_standbyWidget;
    CallDialog *m_callDialog;
    ProgressDialog *m_progressDialog;
#ifdef TARGET_IMX
    NumIPMethod *m_method;
#endif
    QTimer *m_standByTimer;
    int m_standByCount;
};

#endif // UIMODULE_H

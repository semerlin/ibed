#ifndef UIMODULE_H
#define UIMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class UiModulePrivate;

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

public slots:
    /**
     * @brief device register to server success
     */
    void onRegistered();

    /**
     * @brief device register to server failed
     */
    void onRegisterTimeout();

    /**
     * @brief device disconnect from server
     */
    void onDisconnect();

    /**
     * @brief patient name changed
     * @param name - patient name
     */
    void onNameChanged(const QString &name);

    /**
     * @brief patient sex changed
     * @param sex - patient sex
     */
    void onSexChanged(const QString &sex);

    /**
     * @brief patient age changed
     * @param age - patient age
     */
    void onAgeChanged(const QString &age);

    /**
     * @brief patient bed number changed
     * @param bed - bed number
     */
    void onBedChanged(const QString &bed);

    /**
     * @brief patient nurse level changed
     * @param level - nurse level
     *        level will be '0','1','2','3'
     */
    void onLevelChanged(const QString &level);

    /**
     * @brief patient timing of admission changed
     * @param time - timing of admission
     */
    void onTimeChanged(const QString &time);

    /**
     * @brief patient doctor changed
     * @param doctor - doctor name
     */
    void onDoctorChanged(const QString &doctor);

    /**
     * @brief patient eat changed
     * @param eat - patient eat
     */
    void onEatChanged(const QString &eat);

    /**
     * @brief patient nurse changed
     * @param nurse - patient nurse name
     */
    void onNurseChanged(const QString &nurse);

    /**
     * @brief patient doctor advise changed
     * @param advise - patient doctor advise
     */
    void onAdviseChanged(const QString &advise);

    /**
     * @brief patient allergy changed
     * @param allergy - patient allergy
     */
    void onAllergyChanged(const QString &allergy);

    /**
     * @brief add patient advise
     * @param data - new advise
     */
    void onAdviseUpdate(const QString &data);

    /**
     * @brief environment light intensity changed
     * @param intensity - light intensity
     */
    void onLightIntensityChanged(int intensity);

    /**
     * @brief environment temperature changed
     * @param temper - environment temperature
     */
    void onTemperatureChanged(int temper);

    /**
     * @brief environment humidity changed
     * @param humidity - environment humidity
     */
    void onHumidityChanged(int humidity);

    /**
     * @brief environment audio intensity changed
     * @param intensity - audio intensity
     */
    void onAudioIntensityChanged(int intensity);

    /**
     * @brief bed weight changed
     * @param weight - bed weight
     */
    void onWeightChanged(double weight);

    /**
     * @brief infusion input mount changed
     * @param mount - infusion input mount
     */
    void onInfuInputChanged(int mount);

    /**
     * @brief infusion speed changed
     * @param speed - infusion speed
     */
    void onInfuSpeedChanged(int speed);

    /**
     * @brief call out connectting
     */
    void onCallOutConnecting(void);

    /**
     * @brief call in connecting
     */
    void onCallInConnecting(void);

    /**
     * @brief call connectted
     */
    void onCallConnected(void);

    /**
     * @brief call terminate
     */
    void onCallTerminate(void);

    /**
     * @brief touch screen clicked or mouse clicked, keyboard clicked, etc...
     */
    void onClicked(void);

signals:
    /**
     * @brief reconnect to server
     * @param ip - server ip
     * @param port - server port number
     * @param device - device number
     * @param localIp - local device ip
     * @param localMask - local device mask
     * @param localGateway - local device gateway
     */
    void reconnect(const QString &ip, quint16 port, quint16 device,
           const QString &localIp, const QString localMask, const QString localGateway);

    /**
     * @brief doctor advice need to be updated
     */
    void updateAdvise();

    /**
     * @brief patient in out updated
     * @param data - in out data
     */
    void uploadInOut(const QStringList &data);

    /**
     * @brief lcd backlight brightness changed
     * @param value - brightness value
     */
    void brightnessChanged(int value);

    /**
     * @brief lcd backlight turn off time changed
     * @param value - turn off time
     */
    void turnOffTimeChanged(int value);

    /**
     * @brief play some thing
     * @param name
     */
    void play(const QString &name);

    /**
     * @brief pause play
     * @param name
     */
    void pause(const QString &name);

    /**
     * @brief stop play
     * @param name
     */
    void stop(const QString &name);

    /**
     * @brief control bed action
     * @param id - action id
     */
    void bedCtrlPressed(int id);

    /**
     * @brief stop bed action
     * @param id - action id
     */
    void bedCtrlReleased(int id);

    /**
     * @brief start infusion monitor
     */
    void infuStart(void);

    /**
     * @brief stop infusion monitor
     */
    void infuStop(void);

    /**
     * @brief request call out
     */
    void callOutRequest(void);

    /**
     * @brief terminate call
     */
    void callTerminate(void);

private:
    UiModulePrivate * const d_ptr;
    Q_DECLARE_PRIVATE(UiModule)
    Q_DISABLE_COPY(UiModule)
};

#endif // UIMODULE_H

#ifndef UIMODULE_H
#define UIMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"


class MainWidget;
class StandbyWidget;
class CallDialog;
class ProgressDialog;
class NumIPMethod;

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

signals:
    void reconnect(const QString &ip, quint16 port);
    void updateAdvise();
    void uploadInOut(const QStringList &data);
    void clicked(void);
    void brightnessChanged(int value);
    void turnOffTimeChanged(int value);

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

private:
    MainWidget *m_mainWidget;
    StandbyWidget *m_standbyWidget;
    CallDialog *m_callDialog;
    ProgressDialog *m_progressDialog;
#ifdef TARGET_IMX
    NumIPMethod *m_method;
#endif
};

#endif // UIMODULE_H

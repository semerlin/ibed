#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "controls_global.h"
#include <QWidget>
#include <QMap>

namespace Ui {
class MainWidget;
}

class MainTopWidget;
class MainBottomWidget;
class BaseInfoWidget;
class AdviseWidget;
class InOutWidget;
class EducationWidget;
class SettingWidget;
class InfusionWidget;
class BedWidget;

class CONTROLSSHARED_EXPORT MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void setNetworkStatus(const QString &text);
    void setName(const QString &name);
    void setSex(const QString &sex);
    void setAge(const QString &age);
    void setBed(const QString &bed);
    void setLevel(const QString &level);
    void setTime(const QString &time);
    void setDoctor(const QString &doctor);
    void setEat(const QString &eat);
    void setNurse(const QString &nurse);
    void setAdvise(const QString &advise);
    void setAllergy(const QString &allergy);
    void addAdvise(const QString &advise);
    void setLeft(int left);
    void setSpeed(int speed);

signals:
    void reconnect(const QString &ip, quint16 port);
    void updateAdvise(void);
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
    void onTopWidgetButtonClick(int id);
    void onBottomWidgetButtonClick(int id);

private:
    void connectBtnAndWidget(void);

private:
    Ui::MainWidget *ui;
    QWidget *m_lastWidget;
    MainTopWidget *m_topWidget;
    MainBottomWidget *m_bottomWidget;
    BaseInfoWidget *m_baseInfoWidget;
    AdviseWidget *m_adviseWidget;
    InOutWidget *m_inOutWidget;
    EducationWidget *m_educationWidget;
    SettingWidget *m_settingWidget;
    BedWidget *m_bedWidget;
    InfusionWidget *m_infusionWidget;

private:
    QMap<int, QWidget *> m_topBtnWidgets;
    QMap<int, QWidget *> m_bottomBtnWidgets;
};

#endif // MAINWIDGET_H

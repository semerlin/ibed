#ifndef STANDBYWIDGET_H
#define STANDBYWIDGET_H

#include "controls_global.h"
#include "basewidget.h"

namespace Ui {
class StandbyWidget;
}

class CONTROLSSHARED_EXPORT StandbyWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit StandbyWidget(QWidget *parent = 0);
    ~StandbyWidget();

public slots:
    void setName(const QString &name);
    void setBedNum(int num);
    void setNursery(int level);
    void setAge(int age);
    void setLightIntensity(const QString &intensity);
    void setAudioIntensity(const QString &intensity);
    void setTemperature(const QString &temper);
    void setWeight(const QString &weight);
    void setHumidity(const QString &humidity);

private:
    Ui::StandbyWidget *ui;
};

#endif // STANDBYWIDGET_H

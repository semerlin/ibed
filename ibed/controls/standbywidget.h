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


public:
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void setName(const QString &name);
    void setBedNum(int num);
    void setNursery(int level);
    void setAge(int age);
    void setLightIntensity(const QString &intensity);
    void setAudioIntensity(const QString &intensity);

signals:
    void clicked();

private:
    Ui::StandbyWidget *ui;
};

#endif // STANDBYWIDGET_H

#ifndef BASEINFOWIDGET_H
#define BASEINFOWIDGET_H

#include "controls_global.h"
#include <QWidget>

namespace Ui {
class BaseInfoWidget;
}

class CONTROLSSHARED_EXPORT BaseInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseInfoWidget(QWidget *parent = 0);
    ~BaseInfoWidget();

public slots:
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
    void setLevelColor(const QColor &text, const QColor &bk);

private:
    Ui::BaseInfoWidget *ui;
};

#endif // BASEINFOWIDGET_H

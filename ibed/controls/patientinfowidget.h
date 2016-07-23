#ifndef PATIENTINFOWIDGET_H
#define PATIENTINFOWIDGET_H

#include "controls_global.h"
#include "basewidget.h"

namespace Ui {
class PatientInfoWidget;
}

class CONTROLSSHARED_EXPORT PatientInfoWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit PatientInfoWidget(QWidget *parent = 0);
    ~PatientInfoWidget();

public:
    void setContentsMargins(int left, int top, int right, int bottom);

public slots:
    void setData(const QString &data);
    void setInfo(const QString &info);
    void setPixmap(const QPixmap &pixmap);

private:
    Ui::PatientInfoWidget *ui;
};

#endif // PATIENTINFOWIDGET_H

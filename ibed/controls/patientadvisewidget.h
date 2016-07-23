#ifndef PATIENTADVISEWIDGET_H
#define PATIENTADVISEWIDGET_H

#include "controls_global.h"
#include "basewidget.h"

namespace Ui {
class PatientAdviseWidget;
}

class CONTROLSSHARED_EXPORT PatientAdviseWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit PatientAdviseWidget(QWidget *parent = 0);
    ~PatientAdviseWidget();

public slots:
    void setInfo(const QString &info);
    void setData(const QString &data);
    void setDataReadOnly(bool flag);
    void setPixmap(const QPixmap &pixmap);
private:
    Ui::PatientAdviseWidget *ui;
};

#endif // PATIENTADVISEWIDGET_H

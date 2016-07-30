#ifndef INOUTWIDGET_H
#define INOUTWIDGET_H

#include "controls_global.h"
#include "basewidget.h"


namespace Ui {
class InOutWidget;
}

class InoutEditLabelListDelegate;

class CONTROLSSHARED_EXPORT InOutWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit InOutWidget(QWidget *parent = 0);
    ~InOutWidget();

private slots:
    void onPushButtonPress();
    void onPushButtonReleased();
    void onLowlightButton(void);

private:
    Ui::InOutWidget *ui;
    InoutEditLabelListDelegate *m_inDelegate;
    InoutEditLabelListDelegate *m_outDelegate;
};

#endif // INOUTWIDGET_H

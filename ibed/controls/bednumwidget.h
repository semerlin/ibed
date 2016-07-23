#ifndef BEDNUMWIDGET_H
#define BEDNUMWIDGET_H

#include "controls_global.h"
#include "basewidget.h"

namespace Ui {
class BedNumWidget;
}

class CONTROLSSHARED_EXPORT BedNumWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit BedNumWidget(QWidget *parent = 0);
    ~BedNumWidget();

public:
    void setSpacing(int spacing);
    void setContentsMargin(int left, int top, int right, int bottom);

public slots:
    void setText(const QString &name);
    void setBenNum(int num);
    void setPixmap(const QPixmap &pixmap);

private:
    Ui::BedNumWidget *ui;
};

#endif // BEDNUMWIDGET_H

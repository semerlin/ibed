#ifndef SOUNDWIDGET_H
#define SOUNDWIDGET_H

#include "controls_global.h"
#include "basewidget.h"

namespace Ui {
class SoundWidget;
}

class CONTROLSSHARED_EXPORT SoundWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit SoundWidget(QWidget *parent = 0);
    ~SoundWidget();

private:
    Ui::SoundWidget *ui;
};

#endif // SOUNDWIDGET_H

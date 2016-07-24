#ifndef SOUNDWIDGET_H
#define SOUNDWIDGET_H

#include "basewidget.h"

namespace Ui {
class SoundWidget;
}

class SoundWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit SoundWidget(QWidget *parent = 0);
    ~SoundWidget();

private:
    Ui::SoundWidget *ui;
};

#endif // SOUNDWIDGET_H

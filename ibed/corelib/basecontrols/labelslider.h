#ifndef LABELSLIDER_H
#define LABELSLIDER_H

#include <QWidget>

namespace Ui {
class LabelSlider;
}

class LabelSlider : public QWidget
{
    Q_OBJECT

public:
    explicit LabelSlider(QWidget *parent = 0);
    ~LabelSlider();

public slots:
    void setInfo(const QString &info);
    void setPercent(const QString &percent);
    void setSpacing(int spacing);
    void setContentsMargins(int left, int top, int right, int bottom);


private:
    Ui::LabelSlider *ui;
};

#endif // LABELSLIDER_H

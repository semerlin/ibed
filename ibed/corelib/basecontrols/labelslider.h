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

public:
    int value(void) const;

public slots:
    /**
     * @brief set info text in front of slider
     * @param info - information text
     */
    void setInfo(const QString &info);

    /**
     * @brief set percent text
     * @param percent - percent text
     */
    void setPercent(const QString &percent);

    /**
     * @brief set spacing
     * @param spacing - spacing value
     */
    void setSpacing(int spacing);

    /**
     * @brief set contents margins
     * @param left
     * @param top
     * @param right
     * @param bottom
     */
    void setContentsMargins(int left, int top, int right, int bottom);

    /**
     * @brief set slider range
     * @param min - minimum value
     * @param max - maximum value
     */
    void setRange(int min, int max);

    /**
     * @brief set slider value
     * @param val - slider value
     */
    void setValue(int val);

signals:
    void valueChanged(int value);


private:
    Ui::LabelSlider *ui;
};

#endif // LABELSLIDER_H

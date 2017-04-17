#ifndef DOTLABEL_H
#define DOTLABEL_H

#include"basewidget.h"

namespace Ui {
class DotLabel;
}

class DotLabel : public BaseWidget
{
    Q_OBJECT

public:
    explicit DotLabel(QWidget *parent = 0);
    ~DotLabel();

public:
    /**
     * @brief set dot color
     * @param color - dot color
     */
    void setDotColor(const QColor &color);

    /**
     * @brief set label text
     * @param text - label text
     */
    void setText(const QString &text);

    /**
     * @brief set dot and text spacing
     * @param spacing - dot and text sapcing
     */
    void setSpacing(int spacing);

    /**
     * @brief get dot color
     * @return dot color
     */
    QColor dotColor(void) const;

    /**
     * @brief get label text
     * @return label text
     */
    QString text(void) const;

private:
    Ui::DotLabel *ui;
    QColor m_color;
    QString m_text;
};

#endif // DOTLABEL_H

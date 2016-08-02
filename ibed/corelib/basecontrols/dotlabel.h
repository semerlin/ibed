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
    void setDotColor(const QColor &color);
    void setText(const QString &text);
    void setSpacing(int spacing);
    QColor dotColor(void) const;
    QString text(void) const;

private:
    Ui::DotLabel *ui;
    QColor m_color;
    QString m_text;
};

#endif // DOTLABEL_H

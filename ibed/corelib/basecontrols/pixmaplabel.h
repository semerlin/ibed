#ifndef PIXMAPLABEL_H
#define PIXMAPLABEL_H

#include "basewidget.h"

namespace Ui {
class PixmapLabel;
}

class PixmapLabel : public BaseWidget
{
    Q_OBJECT

public:
    explicit PixmapLabel(QWidget *parent = 0);
    ~PixmapLabel();

public:
    void setPixmap(const QPixmap &pixmap);
    void setText(const QString &text);
    void setSpacing(int spacing);
    void setContentsMargins(int left, int top, int right, int bottom);

private:
    Ui::PixmapLabel *ui;
};

#endif // PIXMAPLABEL_H

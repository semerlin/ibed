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
    /**
     * @brief set label pixmap
     * @param pixmap
     */
    void setPixmap(const QPixmap &pixmap);

    /**
     * @brief set label text
     * @param text - label text
     */
    void setText(const QString &text);

    /**
     * @brief set spacing
     * @param spacing
     */
    void setSpacing(int spacing);

    /**
     * @brief set contents margins
     */
    void setContentsMargins(int left, int top, int right, int bottom);

private:
    Ui::PixmapLabel *ui;
};

#endif // PIXMAPLABEL_H

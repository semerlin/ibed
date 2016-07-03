#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include "basecontrols_global.h"
#include <QWidget>

/**
 * @brief qss based widget must inherits from this class
 */
class BASECONTROLSSHARED_EXPORT BaseWidget : public QWidget
{
public:
    explicit BaseWidget(QWidget *parent);
    virtual ~BaseWidget() {}

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // BASEWIDGET_H
#ifndef BASELABEL_H
#define BASELABEL_H

#include "basecontrols_global.h"
#include <QLabel>

class BASECONTROLSSHARED_EXPORT BaseLabel : public QLabel
{
public:
    explicit BaseLabel(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BASELABEL_H

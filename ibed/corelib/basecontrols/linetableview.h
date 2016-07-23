#ifndef LINETABLEVIEW_H
#define LINETABLEVIEW_H

#include "basecontrols_global.h"
#include <QTableView>

class BASECONTROLSSHARED_EXPORT LineTableView : public QTableView
{
public:
    LineTableView(QWidget *parent = 0);
    LineTableView(Qt::Orientation orientation, QWidget *parent = 0);
};

#endif // LINETABLEVIEW_H

#ifndef LINETABLEVIEW_H
#define LINETABLEVIEW_H

#include <QTableView>

class LineTableView : public QTableView
{
public:
    LineTableView(QWidget *parent = 0);
    LineTableView(Qt::Orientation orientation, QWidget *parent = 0);
};

#endif // LINETABLEVIEW_H

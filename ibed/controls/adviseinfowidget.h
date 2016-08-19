#ifndef ADVISEINFOWIDGET_H
#define ADVISEINFOWIDGET_H

#include "controls_global.h"
#include "linetableview.h"
class AdviseInfoModel;

class CONTROLSSHARED_EXPORT AdviseInfoWidget : public LineTableView
{
    Q_OBJECT

public:
    AdviseInfoWidget(QWidget *parent = 0);

public slots:
    void clearData(void);
    void appendData(const QStringList &data);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    AdviseInfoModel *m_model;
    QPoint m_lastPoint;
};

#endif // ADVISEINFOWIDGET_H

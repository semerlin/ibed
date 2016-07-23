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

private:
    AdviseInfoModel *m_model;
};

#endif // ADVISEINFOWIDGET_H

#ifndef ADVISEINFOWIDGET_H
#define ADVISEINFOWIDGET_H

#include <QTableView>

class AdviseInfoPrivate;

class AdviseInfoWidget : public QTableView
{
    Q_OBJECT

public:
    AdviseInfoWidget(QWidget *parent = 0);

public slots:
    void clearData(void);
    void appendData(const QStringList &data);

private:
    AdviseInfoPrivate *d;
};

#endif // ADVISEINFOWIDGET_H

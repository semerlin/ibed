#ifndef CALLWIDGET_H
#define CALLWIDGET_H

#include <QWidget>
#include "basewidget.h"

namespace Ui {
class CallWidget;
}

class CallWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit CallWidget(QWidget *parent = 0);
    ~CallWidget();

public slots:
    void beginTimer(void);
    void endTimer(void);

signals:
    void reject();

private slots:
    void on_pushButtonCancel_clicked();
    void onTimeout();

private:
    Ui::CallWidget *ui;
    QTimer *m_timer;
    int m_timeCnt;
};

#endif // CALLWIDGET_H

#ifndef ADVISEWIDGET_H
#define ADVISEWIDGET_H

#include "controls_global.h"
#include <QWidget>

namespace Ui {
class AdviseWidget;
}

class QTableView;
class AdviseInfoWidget;

class CONTROLSSHARED_EXPORT AdviseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdviseWidget(QWidget *parent = 0);
    ~AdviseWidget();

public:
    void addAdvise(const QString &data);

private slots:
    void onPushButtonPress();
    void onPushButtonReleased();
    void onButtonClicked(int id);

signals:
    void updateClicked();

private:
    void lowlightButtons(int except);

private:
    Ui::AdviseWidget *ui;
    QList<AdviseInfoWidget *> m_adviseInfo;
};

#endif // ADVISEWIDGET_H

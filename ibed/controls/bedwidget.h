#ifndef BEDWIDGET_H
#define BEDWIDGET_H

#include <QWidget>
#include <QPair>
#include <QQueue>

namespace Ui {
class BedWidget;
}

class QTimer;

class BedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BedWidget(QWidget *parent = 0);
    ~BedWidget();

public:
    void setWeight(const QString &weight);

signals:
    void buttonPress(int id);
    void buttonReleased(int id);

private:
    void initButtons(void);

private slots:
    void onButtonPress(void);
    void onButtonReleased(void);
    void onTimeout(void);

private:
    Ui::BedWidget *ui;
    QTimer *m_timer;
    QQueue<QPair<QPair<int, qint64>, bool> > m_pressIDs;
    QQueue<QPair<QPair<int, qint64>, bool> > m_releasedIDs;
};

#endif // BEDWIDGET_H

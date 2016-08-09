#ifndef SERVERETHWIDGET_H
#define SERVERETHWIDGET_H

#include "basewidget.h"

namespace Ui {
class ServerEthWidget;
}

class ServerEthWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit ServerEthWidget(QWidget *parent = 0);
    ~ServerEthWidget();

public:
    QString ip(void) const;
    quint16 port(void) const;

public slots:
    void setStatusText(const QString &text);

signals:
    void reconnect(const QString &ip, quint16 port);

private slots:
    void on_pushButtonConnect_clicked();

private:
    Ui::ServerEthWidget *ui;
};

#endif // SERVERETHWIDGET_H

#ifndef LANCHWIDGET_H
#define LANCHWIDGET_H

#include "iapplancherwidget.h"

namespace Ui {
class LanchWidget;
}

class LanchWidget : public IAppLancherWidget
{
    Q_OBJECT

public:
    explicit LanchWidget(QWidget *parent = 0);
    ~LanchWidget();

public slots:
    void increaseStep();
    void printMsg(const QString &msg);

private:
    Ui::LanchWidget *ui;
};

#endif // LANCHWIDGET_H

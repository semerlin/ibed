#ifndef CALLDIALOG_H
#define CALLDIALOG_H

#include "controls_global.h"
#include <QDialog>

namespace Ui {
class CallDialog;
}

class CONTROLSSHARED_EXPORT CallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CallDialog(QWidget *parent = 0);
    ~CallDialog();

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonAnswer_clicked();

private:
    Ui::CallDialog *ui;
};

#endif // CALLDIALOG_H

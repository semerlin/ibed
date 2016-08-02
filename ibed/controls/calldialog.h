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

private:
    Ui::CallDialog *ui;
};

#endif // CALLDIALOG_H

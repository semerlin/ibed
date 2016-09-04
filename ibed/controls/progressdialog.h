#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include "controls_global.h"
#include <QDialog>

namespace Ui {
class ProgressDialog;
}

class CONTROLSSHARED_EXPORT ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = 0);
    ~ProgressDialog();

public slots:
    void setProgress(int progress);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ProgressDialog *ui;
};

#endif // PROGRESSDIALOG_H

#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->pushButton->setText(QT_TRANSLATE_NOOP("Progress", "取 消"));

    setProgress(100);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::setProgress(int progress)
{
    ui->widgetProgress->setText(QString::number(progress));
    ui->widgetProgress->setValue(progress);
}

#include "calldialog.h"
#include "ui_calldialog.h"

CallDialog::CallDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setModal(false);

    ui->labelStep->setText(QT_TRANSLATE_NOOP("Call", "护士站"));
    ui->labelTime->setText("00:00:00");
}

CallDialog::~CallDialog()
{
    delete ui;
}

void CallDialog::on_pushButtonCancel_clicked()
{
    reject();
}

void CallDialog::on_pushButtonAnswer_clicked()
{

}

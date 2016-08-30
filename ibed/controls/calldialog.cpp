#include "calldialog.h"
#include "ui_calldialog.h"

CallDialog::CallDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setModal(false);
}

CallDialog::~CallDialog()
{
    delete ui;
}

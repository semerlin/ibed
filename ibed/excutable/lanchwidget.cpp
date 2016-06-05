#include "lanchwidget.h"
#include "ui_lanchwidget.h"

LanchWidget::LanchWidget(QWidget *parent) :
    IAppLancherWidget(parent),
    ui(new Ui::LanchWidget)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
}

LanchWidget::~LanchWidget()
{
    delete ui;
}

void LanchWidget::increaseStep()
{

}

void LanchWidget::printMsg(const QString &msg)
{
    ui->label_message->setText(msg);
}

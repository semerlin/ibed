#include "launchwidget.h"
#include "ui_launchwidget.h"
#include "launchwidget_p.h"

LaunchWidget::LaunchWidget(QWidget *parent) :
    IAppLaunchWidget(parent),
    ui(new Ui::LaunchWidget),
    d_ptr(new LaunchWidgetPrivate)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->progressBar_launch->setValue(0);
}

LaunchWidget::~LaunchWidget()
{
    delete ui;
    delete d_ptr;
}

void LaunchWidget::setSteps(int steps)
{
    Q_D(LaunchWidget);
    d->m_totalStep = steps;
    ui->progressBar_launch->setRange(0, steps);
}

void LaunchWidget::increaseStep()
{
    Q_D(LaunchWidget);
    d->m_currentStep ++;
    if(d->m_currentStep > d->m_totalStep)
        d->m_currentStep = d->m_totalStep;

    ui->progressBar_launch->setValue(d->m_currentStep);
}

void LaunchWidget::printMsg(const QString &msg)
{
    ui->label_message->setText(msg);
}

#include "launchwidget.h"
#include "ui_launchwidget.h"

LaunchWidget::LaunchWidget(QWidget *parent) :
    IAppLaunchWidget(parent),
    ui(new Ui::LaunchWidget),
    m_currentVal(0),
    m_maxVal(0),
    m_minVal(0)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->progressBar_launch->setValue(m_currentVal);
}

LaunchWidget::~LaunchWidget()
{
    delete ui;
}

void LaunchWidget::setRange(int min, int max)
{
    m_minVal = min;
    m_maxVal = max;
    ui->progressBar_launch->setRange(min, max);
}

void LaunchWidget::increaseStep()
{
    m_currentVal ++;
    if(m_currentVal > m_maxVal)
        m_currentVal = m_maxVal;

    ui->progressBar_launch->setValue(m_currentVal);
}

void LaunchWidget::printMsg(const QString &msg)
{
    ui->label_message->setText(msg);
}

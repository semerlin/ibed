#include "lanchwidget.h"
#include "ui_lanchwidget.h"

LanchWidget::LanchWidget(QWidget *parent) :
    IAppLaunchWidget(parent),
    ui(new Ui::LanchWidget),
    m_currentVal(0),
    m_maxVal(0),
    m_minVal(0)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->progressBar_launch->setValue(m_currentVal);
}

LanchWidget::~LanchWidget()
{
    delete ui;
}

void LanchWidget::setRange(int min, int max)
{
    ui->progressBar_launch->setRange(min, max);
}

void LanchWidget::increaseStep()
{
    m_currentVal ++;
    if(m_currentVal > m_maxVal)
        m_currentVal = m_maxVal;

    ui->progressBar_launch->setValue(m_currentVal);
}

void LanchWidget::printMsg(const QString &msg)
{
    ui->label_message->setText(msg);
}

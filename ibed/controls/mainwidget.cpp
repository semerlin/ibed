#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "maintopwidget.h"
#include "mainbottomwidget.h"
#include "baseinfowidget.h"
#include "advisewidget.h"
#include "inoutwidget.h"
#include "educationwidget.h"
#include "settingwidget.h"
#include "bedwidget.h"
#include "infusionwidget.h"
#include "boost/foreach.hpp"
#include <QPushButton>
#include "util.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_lastWidget(NULL),
    m_topWidget(new MainTopWidget(this)),
    m_bottomWidget(new MainBottomWidget(this)),
    m_baseInfoWidget(new BaseInfoWidget(this)),
    m_adviseWidget(new AdviseWidget(this)),
    m_inOutWidget(new InOutWidget(this)),
    m_educationWidget(new EducationWidget(this)),
    m_settingWidget(new SettingWidget(this)),
    m_bedWidget(new BedWidget(this)),
    m_infusionWidget(new InfusionWidget(this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->verticalLayoutTop->addWidget(m_topWidget);
    connect(m_topWidget, SIGNAL(buttonClicked(int)), this, SLOT(onTopWidgetButtonClick(int)));

    ui->verticalLayoutBottom->addWidget(m_bottomWidget);
    connect(m_bottomWidget, SIGNAL(buttonClicked(int)), this, SLOT(onBottomWidgetButtonClick(int)));

    ui->verticalLayoutMiddle->addWidget(m_baseInfoWidget);
    ui->verticalLayoutMiddle->addWidget(m_adviseWidget);
    ui->verticalLayoutMiddle->addWidget(m_inOutWidget);
    ui->verticalLayoutMiddle->addWidget(m_educationWidget);
    ui->verticalLayoutMiddle->addWidget(m_settingWidget);
    ui->verticalLayoutMiddle->addWidget(m_bedWidget);
    ui->verticalLayoutMiddle->addWidget(m_infusionWidget);

    m_baseInfoWidget->show();
    m_adviseWidget->hide();
    m_inOutWidget->hide();
    m_educationWidget->hide();
    m_settingWidget->hide();
    m_bedWidget->hide();
    m_infusionWidget->hide();

    m_lastWidget = m_baseInfoWidget;

    connectBtnAndWidget();

    //connect signals
    connect(m_settingWidget, SIGNAL(reconnect(QString, quint16)),
            this, SIGNAL(reconnect(QString, quint16)));

    connect(m_adviseWidget, SIGNAL(updateClicked()), this, SIGNAL(updateAdvise()));

    connect(m_inOutWidget, SIGNAL(upload(QStringList)), this, SIGNAL(uploadInOut(QStringList)));

    connect(m_settingWidget, SIGNAL(brightnessChanged(int)), this, SIGNAL(brightnessChanged(int)));
    connect(m_settingWidget, SIGNAL(turnOffTimeChanged(int)), this, SIGNAL(turnOffTimeChanged(int)));

    connect(m_educationWidget, SIGNAL(play(QString)), this, SIGNAL(play(QString)));
    connect(m_educationWidget, SIGNAL(pause(QString)), this, SIGNAL(pause(QString)));
    connect(m_educationWidget, SIGNAL(stop(QString)), this, SIGNAL(stop(QString)));

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setNetworkStatus(const QString &text)
{
    m_settingWidget->setStatusText(text);
}

void MainWidget::setName(const QString &name)
{
    m_baseInfoWidget->setName(name);
}

void MainWidget::setSex(const QString &sex)
{
    m_baseInfoWidget->setSex(sex);
}

void MainWidget::setAge(const QString &age)
{
    m_baseInfoWidget->setAge(age + "岁");
}

void MainWidget::setBed(const QString &bed)
{
    m_baseInfoWidget->setBed(bed);
}

void MainWidget::setLevel(const QString &level)
{
    m_baseInfoWidget->setLevel(level);
}

void MainWidget::setTime(const QString &time)
{
    m_baseInfoWidget->setTime(time);
}

void MainWidget::setDoctor(const QString &doctor)
{
    m_baseInfoWidget->setDoctor(doctor);
}

void MainWidget::setEat(const QString &eat)
{
    m_baseInfoWidget->setEat(eat);
}

void MainWidget::setNurse(const QString &nurse)
{
    m_baseInfoWidget->setNurse(nurse);
}

void MainWidget::setAdvise(const QString &advise)
{
    m_baseInfoWidget->setAdvise(advise);
}

void MainWidget::setAllergy(const QString &allergy)
{
    m_baseInfoWidget->setAllergy(allergy);
}

void MainWidget::addAdvise(const QString &advise)
{
    m_adviseWidget->addAdvise(advise);
}

void MainWidget::onTopWidgetButtonClick(int id)
{
    //lowlight buttons if clicked
    m_bottomWidget->lowlightButtons();

    if((m_lastWidget != m_topBtnWidgets[id]) && (m_topBtnWidgets[id] != NULL))
    {
        m_lastWidget->hide();
        m_topBtnWidgets[id]->show();
        m_lastWidget = m_topBtnWidgets[id];
    }
}

void MainWidget::onBottomWidgetButtonClick(int id)
{
    //lowlight buttons if clicked
    m_topWidget->lowlightButtons();

    if((m_lastWidget != m_bottomBtnWidgets[id]) && (m_bottomBtnWidgets[id] != NULL))
    {
        m_lastWidget->hide();
        m_bottomBtnWidgets[id]->show();
        m_lastWidget = m_bottomBtnWidgets[id];
    }
}

void MainWidget::connectBtnAndWidget()
{
    m_topBtnWidgets.clear();
    m_topBtnWidgets[0] = m_baseInfoWidget;
    m_topBtnWidgets[1] = m_adviseWidget;
    m_topBtnWidgets[2] = m_inOutWidget;
    m_topBtnWidgets[3] = m_educationWidget;
    m_topBtnWidgets[4] = m_settingWidget;

    m_bottomBtnWidgets[0] = m_bedWidget;
    m_bottomBtnWidgets[1] = m_infusionWidget;
}




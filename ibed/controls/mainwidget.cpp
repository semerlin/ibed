#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "maintopwidget.h"
#include "mainbottomwidget.h"
#include "baseinfowidget.h"
#include "advisewidget.h"
#include "boost/foreach.hpp"
#include <QPushButton>
#include "util.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_lastWidget(NULL),
    m_topWidget(new MainTopWidget(this)),
    m_bottomWidget(new MainBottomWidget(this)),
    m_baseInfoWidget(new BaseInfoWidget(this)),
    m_adviseWidget(new AdviseWidget(this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->verticalLayoutTop->addWidget(m_topWidget);
    connect(m_topWidget, SIGNAL(buttonClicked(int)), this, SLOT(onTopWidgetButtonClick(int)));

    ui->verticalLayoutBottom->addWidget(m_bottomWidget);
    connect(m_bottomWidget, SIGNAL(buttonClicked(int)), this, SLOT(onBottomWidgetButtonClick(int)));

    ui->verticalLayoutMiddle->addWidget(m_baseInfoWidget);
    ui->verticalLayoutMiddle->addWidget(m_adviseWidget);
    m_baseInfoWidget->show();
    m_adviseWidget->hide();

    m_lastWidget = m_baseInfoWidget;

    connectBtnAndWidget();

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::onTopWidgetButtonClick(int id)
{
    //lowlight buttons if clicked
    m_bottomWidget->lowlightButtons();

    if((m_lastWidget != m_btnWidgets[id]) && (m_btnWidgets[id] != NULL))
    {
        m_lastWidget->hide();
        m_btnWidgets[id]->show();
        m_lastWidget = m_btnWidgets[id];
    }
}

void MainWidget::onBottomWidgetButtonClick(int id)
{
    //lowlight buttons if clicked
    m_topWidget->lowlightButtons();

    switch(id)
    {
    case 0:
        break;
    default:
        break;
    }
}

void MainWidget::connectBtnAndWidget()
{
    m_btnWidgets.clear();
    m_btnWidgets[0] = m_baseInfoWidget;
    m_btnWidgets[1] = m_adviseWidget;
}



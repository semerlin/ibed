#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "maintopwidget.h"
#include "mainbottomwidget.h"
#include "boost/foreach.hpp"
#include <QPushButton>
#include "util.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_topWidget(new MainTopWidget(this)),
    m_bottomWidget(new MainBottomWidget(this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->verticalLayoutTop->addWidget(m_topWidget);
    connect(m_topWidget, SIGNAL(buttonClicked(int)), this, SLOT(onTopWidgetButtonClick(int)));

    ui->verticalLayoutBottom->addWidget(m_bottomWidget);
    connect(m_bottomWidget, SIGNAL(buttonClicked(int)), this, SLOT(onBottomWidgetButtonClick(int)));

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::onTopWidgetButtonClick(int id)
{
    //lowlight buttons if clicked
    m_bottomWidget->lowlightButtons();

    switch(id)
    {
    case 0:
        break;
    default:
        break;
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



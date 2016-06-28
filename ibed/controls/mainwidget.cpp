#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "maintopwidget.h"
#include "boost/foreach.hpp"
#include <QPushButton>
#include "util.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    m_topWidget(new MainTopWidget(this))
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->verticalLayoutTop->addWidget(m_topWidget);
    connect(m_topWidget, SIGNAL(buttonClicked(int)), this, SLOT(onTopWidgetButtonClick(int)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::onTopWidgetButtonClick(int id)
{
    switch(id)
    {
    case 0:
        break;
    default:
        break;
    }
}



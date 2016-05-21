#include "maintopwidget.h"
#include "ui_maintopwidget.h"

MainTopWidget::MainTopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTopWidget)
{
    ui->setupUi(this);
}

MainTopWidget::~MainTopWidget()
{
    delete ui;
}

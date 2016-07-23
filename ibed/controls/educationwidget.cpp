#include "educationwidget.h"
#include "ui_educationwidget.h"

EducationWidget::EducationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationWidget)
{
    ui->setupUi(this);
}

EducationWidget::~EducationWidget()
{
    delete ui;
}

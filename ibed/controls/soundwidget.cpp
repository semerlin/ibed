#include "soundwidget.h"
#include "ui_soundwidget.h"

SoundWidget::SoundWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

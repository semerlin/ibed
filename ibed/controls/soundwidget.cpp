#include "soundwidget.h"
#include "ui_soundwidget.h"

SoundWidget::SoundWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    ui->widgetSound->setContentsMargins(0, 0, 25, 0);
    ui->widgetSound->setInfo("Sound   ");
    ui->widgetSound->setPercent("  90");

    ui->labelPic->setPixmap(QPixmap(":/res/images/sound.png"));
    ui->labelName->setText("音量设置");
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

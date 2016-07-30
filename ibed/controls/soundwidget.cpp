#include "soundwidget.h"
#include "ui_soundwidget.h"

SoundWidget::SoundWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    ui->widgetSound->setContentsMargins(0, 0, 25, 0);
    ui->widgetSound->setInfo(QT_TRANSLATE_NOOP("Sound", "音量大小   "));
    ui->widgetSound->setPercent("  90");

    ui->labelPic->setPixmap(QPixmap(":/res/images/sound.png"));
    ui->labelName->setText(QT_TRANSLATE_NOOP("Sound", "音量设置"));
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

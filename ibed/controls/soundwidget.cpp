#include "soundwidget.h"
#include "ui_soundwidget.h"
#include "appsetting.h"

SoundWidget::SoundWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    ui->widgetSound->setContentsMargins(0, 0, 25, 0);
    ui->widgetSound->setInfo(QT_TRANSLATE_NOOP("Sound", "音量大小   "));
    ui->widgetSound->setPercent("  " + QString::number(AppSetting::instance().value(AppSetting::Sound).toUInt()));
    ui->widgetSound->setRange(0, 100);
    ui->widgetSound->setValue(AppSetting::instance().value(AppSetting::Sound).toUInt());
    connect(ui->widgetSound, SIGNAL(valueChanged(int)), this, SLOT(onSoundChanged(int)));

    ui->labelPic->setPixmap(QPixmap(":/res/images/sound.png"));
    ui->labelName->setText(QT_TRANSLATE_NOOP("Sound", "音量设置"));
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

int SoundWidget::sound() const
{
    return ui->widgetSound->value();
}

void SoundWidget::onSoundChanged(int value)
{
    ui->widgetSound->setPercent("  " + QString::number(value));
    emit soundChanged(value);
}

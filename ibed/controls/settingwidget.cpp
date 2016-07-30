#include "settingwidget.h"
#include "ui_settingwidget.h"
#include "util.h"

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    ui->pushButtonSave->setIcons(QStringList()
                                    << ":/res/images/upload_l.png"
                                    << ":/res/images/upload_h.png");
    ui->pushButtonSave->setText(QT_TRANSLATE_NOOP("Setting" ,"保存"));
    connect(ui->pushButtonSave, SIGNAL(pressed()), this, SLOT(onPushButtonPress()));
    connect(ui->pushButtonSave, SIGNAL(released()), this, SLOT(onPushButtonReleased()));

}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::onPushButtonPress()
{
    Util::changeQssWidgetProperty(ui->pushButtonSave, "highlight", true);
    ui->pushButtonSave->changeToIcon(1);
}

void SettingWidget::onPushButtonReleased()
{
    Util::changeQssWidgetProperty(ui->pushButtonSave, "highlight", false);
    ui->pushButtonSave->changeToIcon(0);
}

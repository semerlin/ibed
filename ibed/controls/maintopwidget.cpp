#include <QPushButton>
#include "maintopwidget.h"
#include "ui_maintopwidget.h"
#include "boost/foreach.hpp"
#include "iconbuttonbox.h"
#include "util.h"

#define BUTTON_TYPE QPushButton

MainTopWidget::MainTopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTopWidget)
{
    ui->setupUi(this);
    ui->widgetTop->setSpacing(40);
    ui->widgetTop->setContentsMargins(20, 0, 20, 0);

    ui->widgetTop->addButton<BUTTON_TYPE>(QT_TRANSLATE_NOOP("TopWidget", "基本信息"));
    ui->widgetTop->setButtonIcons(0, QStringList()
                                 << ":/res/images/baseinfo_l.png"
                                 << ":/res/images/baseinfo_h.png");

    ui->widgetTop->addButton<BUTTON_TYPE>(QT_TRANSLATE_NOOP("TopWidget", "医嘱内容"));
    ui->widgetTop->setButtonIcons(1, QStringList()
                                 << ":/res/images/advise_l.png"
                                 << ":/res/images/advise_h.png");

    ui->widgetTop->addButton<BUTTON_TYPE>(QT_TRANSLATE_NOOP("TopWidget", "出入量"));
    ui->widgetTop->setButtonIcons(2, QStringList()
                                 << ":/res/images/inout_l.png"
                                 << ":/res/images/inout_h.png");

    ui->widgetTop->addButton<BUTTON_TYPE>(QT_TRANSLATE_NOOP("TopWidget", "医疗宣教"));
    ui->widgetTop->setButtonIcons(3, QStringList()
                                 << ":/res/images/education_l.png"
                                 << ":/res/images/education_h.png");

    ui->widgetTop->addButton<BUTTON_TYPE>(QT_TRANSLATE_NOOP("TopWidget", "系统设置"));
    ui->widgetTop->setButtonIcons(4, QStringList()
                                 << ":/res/images/setting_l.png"
                                 << ":/res/images/setting_h.png");

    connect(ui->widgetTop, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));

    if(ui->widgetTop->button<BUTTON_TYPE>(0) != NULL)
    {
        ui->widgetTop->button<BUTTON_TYPE>(0)->setProperty("highlight", true);
        ui->widgetTop->changeToIcon(0, 1);
    }
}


MainTopWidget::~MainTopWidget()
{
    delete ui;
}

void MainTopWidget::lowlightButtons()
{
    QList<BUTTON_TYPE *> buttons = ui->widgetTop->buttons<BUTTON_TYPE>();
    int count = buttons.count();
    BOOST_FOREACH(BUTTON_TYPE *btn, buttons)
    {
        Util::changeQssWidgetProperty(btn, "highlight", false);
    }

    for(int i = 0; i < count; i++)
    {
        ui->widgetTop->changeToIcon(i, 0);
    }
}


void MainTopWidget::lowlightButtons(int except)
{
    QList<BUTTON_TYPE *> buttons = ui->widgetTop->buttons<BUTTON_TYPE>();
    int count = buttons.count();
    BOOST_FOREACH(BUTTON_TYPE *btn, buttons)
    {
        Util::changeQssWidgetProperty(btn, "highlight", false);
    }

    for(int i = 0; i < count; i++)
    {
        if(i != except)
            ui->widgetTop->changeToIcon(i, 0);
    }
}

void MainTopWidget::onButtonClicked(int id)
{
    lowlightButtons(id);
    Util::changeQssWidgetProperty(ui->widgetTop->button<BUTTON_TYPE>(id), "highlight", true);
    ui->widgetTop->changeToIcon(id, 1);

    emit buttonClicked(id);
}


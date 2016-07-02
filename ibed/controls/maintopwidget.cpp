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

    ui->widgetTop->addButton<BUTTON_TYPE>(tr("Patient"));
    ui->widgetTop->setButtonIcon(0, QStringList()
                                 << "./resource/ui/icon/baseinfo_l.png"
                                 << "./resource/ui/icon/baseinfo_h.png");

    ui->widgetTop->addButton<BUTTON_TYPE>(tr("Advise"));
    ui->widgetTop->setButtonIcon(1, QStringList()
                                 << "./resource/ui/icon/advise_l.png"
                                 << "./resource/ui/icon/advise_h.png");

    ui->widgetTop->addButton<BUTTON_TYPE>(tr("In Out"));
    ui->widgetTop->setButtonIcon(2, QStringList()
                                 << "./resource/ui/icon/inout_l.png"
                                 << "./resource/ui/icon/inout_h.png");

    ui->widgetTop->addButton<BUTTON_TYPE>(tr("Education"));
    ui->widgetTop->setButtonIcon(3, QStringList()
                                 << "./resource/ui/icon/education_l.png"
                                 << "./resource/ui/icon/education_h.png");

    ui->widgetTop->addButton<BUTTON_TYPE>(tr("Setting"));
    ui->widgetTop->setButtonIcon(4, QStringList()
                                 << "./resource/ui/icon/setting_l.png"
                                 << "./resource/ui/icon/setting_h.png");

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
        Util::instance().changeQssWidgetProperty(btn, "highlight", false);
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
        Util::instance().changeQssWidgetProperty(btn, "highlight", false);
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
    Util::instance().changeQssWidgetProperty(ui->widgetTop->button<BUTTON_TYPE>(id), "highlight", true);
    ui->widgetTop->changeToIcon(id, 1);

    emit buttonClicked(id);
}


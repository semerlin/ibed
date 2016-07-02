#include "mainbottomwidget.h"
#include "ui_mainbottomwidget.h"
#include "boost/foreach.hpp"
#include "util.h"
#include <QPushButton>

#define BUTTON_TYPE QPushButton

MainBottomWidget::MainBottomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainBottomWidget)
{
    ui->setupUi(this);
    ui->widgetBottom->setSpacing(100);

    ui->widgetBottom->addButton<BUTTON_TYPE>(tr("Bed"));
    ui->widgetBottom->setButtonIcon(0, QStringList()
                                 << "./resource/ui/icon/bedcontrol_l.png"
                                 << "./resource/ui/icon/bedcontrol_h.png");

    ui->widgetBottom->addButton<BUTTON_TYPE>(tr("Infusion"));
    ui->widgetBottom->setButtonIcon(1, QStringList()
                                 << "./resource/ui/icon/infusion_l.png"
                                 << "./resource/ui/icon/infusion_h.png");

    connect(ui->widgetBottom, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));
}

MainBottomWidget::~MainBottomWidget()
{
    delete ui;
}

void MainBottomWidget::lowlightButtons()
{
    QList<BUTTON_TYPE *> buttons = ui->widgetBottom->buttons<BUTTON_TYPE>();
    int count = buttons.count();
    BOOST_FOREACH(BUTTON_TYPE *btn, buttons)
    {
        Util::instance().changeQssWidgetProperty(btn, "highlight", false);
    }

    for(int i = 0; i < count; i++)
    {
        ui->widgetBottom->changeToIcon(i, 0);
    }
}

void MainBottomWidget::lowlightButtons(int except)
{
    QList<BUTTON_TYPE *> buttons = ui->widgetBottom->buttons<BUTTON_TYPE>();
    int count = buttons.count();
    BOOST_FOREACH(BUTTON_TYPE *btn, buttons)
    {
        Util::instance().changeQssWidgetProperty(btn, "highlight", false);
    }

    for(int i = 0; i < count; i++)
    {
        if(i != except)
            ui->widgetBottom->changeToIcon(i, 0);
    }
}

void MainBottomWidget::onButtonClicked(int id)
{
    lowlightButtons(id);
    Util::instance().changeQssWidgetProperty(ui->widgetBottom->button<BUTTON_TYPE>(id), "highlight", true);
    ui->widgetBottom->changeToIcon(id, 1);

    emit buttonClicked(id);
}

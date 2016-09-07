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
    ui->widgetBottom->setContentsMargins(100, 0, 100, 0);

    ui->widgetBottom->addButton<BUTTON_TYPE>(QT_TRANSLATE_NOOP("BottomWidget", "病床控制"));
    ui->widgetBottom->setButtonIcons(0, QStringList()
                                 << ":/res/images/bedcontrol_l.png"
                                 << ":/res/images/bedcontrol_h.png");

    ui->widgetBottom->addButton<BUTTON_TYPE>(QT_TRANSLATE_NOOP("BottomWidget", "输液控制"));
    ui->widgetBottom->setButtonIcons(1, QStringList()
                                 << ":/res/images/infusion_l.png"
                                 << ":/res/images/infusion_h.png");

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
        Util::changeQssWidgetProperty(btn, "highlight", false);
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
        Util::changeQssWidgetProperty(btn, "highlight", false);
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
    Util::changeQssWidgetProperty(ui->widgetBottom->button<BUTTON_TYPE>(id), "highlight", true);
    ui->widgetBottom->changeToIcon(id, 1);

    emit buttonClicked(id);
}

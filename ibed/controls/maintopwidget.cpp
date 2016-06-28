#include <QPushButton>
#include "maintopwidget.h"
#include "ui_maintopwidget.h"
#include "boost/foreach.hpp"
#include "basebuttonbox.h"
#include "util.h"

#define BUTTON_TYPE QPushButton

MainTopWidget::MainTopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainTopWidget)
{
    ui->setupUi(this);
    ui->widgetTop->setSpacing(40);
    ui->widgetTop->addButton<BUTTON_TYPE>(tr("Patient"));
    ui->widgetTop->addButton<BUTTON_TYPE>(tr("Advise"));
    ui->widgetTop->addButton<BUTTON_TYPE>(tr("In Out"));
    ui->widgetTop->addButton<BUTTON_TYPE>(tr("Education"));
    ui->widgetTop->addButton<BUTTON_TYPE>(tr("Setting"));

    ui->widgetTop->button<BUTTON_TYPE>(0)->setIcon(QIcon("./resource/ui/icon/baseinfo.png"));
    ui->widgetTop->button<BUTTON_TYPE>(1)->setIcon(QIcon("./resource/ui/icon/advise.png"));
    ui->widgetTop->button<BUTTON_TYPE>(2)->setIcon(QIcon("./resource/ui/icon/inout.png"));
    ui->widgetTop->button<BUTTON_TYPE>(3)->setIcon(QIcon("./resource/ui/icon/education.png"));
    ui->widgetTop->button<BUTTON_TYPE>(4)->setIcon(QIcon("./resource/ui/icon/setting.png"));

    connect(ui->widgetTop, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));

    if(ui->widgetTop->button<BUTTON_TYPE>(0) != NULL)
        ui->widgetTop->button<BUTTON_TYPE>(0)->setProperty("highlight", true);
}

MainTopWidget::~MainTopWidget()
{
    delete ui;
}

BUTTON_TYPE *MainTopWidget::button(int id) const
{
    return ui->widgetTop->button<BUTTON_TYPE>(id);
}

const QList<BUTTON_TYPE *> MainTopWidget::buttons() const
{
    return ui->widgetTop->buttons<BUTTON_TYPE>();
}

void MainTopWidget::lowlightButtons()
{
    QList<BUTTON_TYPE *> buttons = ui->widgetTop->buttons<BUTTON_TYPE>();
    BOOST_FOREACH(BUTTON_TYPE *btn, buttons)
    {
        Util::instance().changeQssWidgetProperty(btn, "highlight", false);
    }
}

void MainTopWidget::onButtonClicked(int id)
{
    lowlightButtons();
    Util::instance().changeQssWidgetProperty(ui->widgetTop->button<BUTTON_TYPE>(id), "highlight", true);

    emit buttonClicked(id);
}


#include "adviseinfowidget.h"
#include "advisewidget.h"
#include "ui_advisewidget.h"
#include "util.h"
#include <QTimer>
#include "boost/foreach.hpp"

AdviseWidget::AdviseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdviseWidget)
{
    ui->setupUi(this);

    ui->pushButtonRefresh->setIcons(QStringList()
                                    << ":/res/images/refresh_l.png"
                                    << ":/res/images/refresh_h.png");

    ui->pushButtonRefresh->setText(tr("Update"));

    ui->widgetTabBar->addButton<QPushButton>(tr("Temp Advise"));
    ui->widgetTabBar->setButtonIcons(0, QStringList()
                                 << ":/res/images/shortadvise_l.png"
                                 << ":/res/images/shortadvise_h.png");

    ui->widgetTabBar->addButton<QPushButton>(tr("Long Advise"));
    ui->widgetTabBar->setButtonIcons(1, QStringList()
                                 << ":/res/images/longadvise_l.png"
                                 << ":/res/images/longadvise_h.png");

    ui->widgetTabBar->setContentsMargins(1, 1, 440, 0);
    if(ui->widgetTabBar->button<QPushButton>(0) != NULL)
    {
        ui->widgetTabBar->button<QPushButton>(0)->setProperty("highlight", true);
        ui->widgetTabBar->changeToIcon(0, 1);
    }

    connect(ui->widgetTabBar, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));

    m_adviseInfo.append(new AdviseInfoWidget);
    m_adviseInfo.append(new AdviseInfoWidget);
    ui->stackedWidget->addWidget(m_adviseInfo.at(0));
    m_adviseInfo.at(0)->appendData(QStringList() << "a" << "a");
    ui->stackedWidget->addWidget(m_adviseInfo.at(1));
    m_adviseInfo.at(1)->appendData(QStringList() << "b" << "b");
    ui->stackedWidget->setCurrentIndex(1);
    m_adviseInfo.at(0)->show();
}

AdviseWidget::~AdviseWidget()
{
    delete ui;
}

void AdviseWidget::on_pushButtonRefresh_clicked()
{
    Util::changeQssWidgetProperty(ui->pushButtonRefresh, "highlight", true);
    ui->pushButtonRefresh->changeToIcon(1);
    QTimer::singleShot(150, this, SLOT(onLowlightPushButton()));
}

void AdviseWidget::onLowlightPushButton()
{
    ui->pushButtonRefresh->changeToIcon(0);
    Util::changeQssWidgetProperty(ui->pushButtonRefresh, "highlight", false);
}


void AdviseWidget::lowlightButtons(int except)
{
    QList<QPushButton *> buttons = ui->widgetTabBar->buttons<QPushButton>();
    int count = buttons.count();
    BOOST_FOREACH(QPushButton *btn, buttons)
    {
        Util::changeQssWidgetProperty(btn, "highlight", false);
    }

    for(int i = 0; i < count; i++)
    {
        if(i != except)
            ui->widgetTabBar->changeToIcon(i, 0);
    }
}

void AdviseWidget::onButtonClicked(int id)
{
    lowlightButtons(id);
    Util::changeQssWidgetProperty(ui->widgetTabBar->button<QPushButton>(id), "highlight", true);
    ui->widgetTabBar->changeToIcon(id, 1);

    ui->stackedWidget->setCurrentIndex(id);
    m_adviseInfo.at(id ^ 1)->hide();
    m_adviseInfo.at(id)->show();
}


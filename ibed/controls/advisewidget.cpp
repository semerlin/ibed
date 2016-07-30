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

    ui->pushButtonRefresh->setText(QT_TRANSLATE_NOOP("AdviseInfo", "更新"));
    connect(ui->pushButtonRefresh, SIGNAL(pressed()), this, SLOT(onPushButtonPress()));
    connect(ui->pushButtonRefresh, SIGNAL(released()), this, SLOT(onPushButtonReleased()));

    ui->widgetTabBar->addButton<QPushButton>(QT_TRANSLATE_NOOP("AdviseInfo", "临时医嘱"));
    ui->widgetTabBar->setButtonIcons(0, QStringList()
                                 << ":/res/images/shortadvise_l.png"
                                 << ":/res/images/shortadvise_h.png");

    ui->widgetTabBar->addButton<QPushButton>(QT_TRANSLATE_NOOP("AdviseInfo", "长期医嘱"));
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
    ui->verticalLayoutTemp->addWidget(m_adviseInfo.at(0));
    ui->verticalLayoutLong->addWidget(m_adviseInfo.at(1));
    m_adviseInfo.at(0)->setObjectName("tempAdvise");
    m_adviseInfo.at(1)->setObjectName("longAdvise");
    m_adviseInfo.at(0)->appendData(QStringList() << "a" << "a");
    m_adviseInfo.at(0)->appendData(QStringList() << "b" << "b");
    m_adviseInfo.at(0)->appendData(QStringList() << "c" << "c");
    m_adviseInfo.at(0)->appendData(QStringList() << "d" << "d");

    m_adviseInfo.at(1)->appendData(QStringList() << "1" << "1");
    m_adviseInfo.at(1)->appendData(QStringList() << "2" << "2");
    m_adviseInfo.at(1)->appendData(QStringList() << "3" << "3");
    m_adviseInfo.at(1)->appendData(QStringList() << "4" << "4");
    ui->stackedWidget->setCurrentIndex(0);
}

AdviseWidget::~AdviseWidget()
{
    delete ui;
}



void AdviseWidget::onPushButtonPress()
{
    Util::changeQssWidgetProperty(ui->pushButtonRefresh, "highlight", true);
    ui->pushButtonRefresh->changeToIcon(1);
}

void AdviseWidget::onPushButtonReleased()
{
    Util::changeQssWidgetProperty(ui->pushButtonRefresh, "highlight", false);
    ui->pushButtonRefresh->changeToIcon(0);
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
}


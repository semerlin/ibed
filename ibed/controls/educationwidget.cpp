#include "educationwidget.h"
#include "ui_educationwidget.h"
#include "appuiconfig.h"
#include "musicplaylistitem.h"

EducationWidget::EducationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationWidget),
    m_height(0)
{
    ui->setupUi(this);

    QFont font(AppUiConfig::instance().fontFamily());
    font.setPixelSize(12);
    m_height = QFontMetrics(font).height() + 15;

    ui->listView->addItem(new MusicPlayListItem("           曲目1:",
                                                ":/res/images/play.png",
                                                ":/res/images/pause.png",
                                                ":/res/images/stop.png"));

    ui->listView->addItem(new MusicPlayListItem("           曲目2:",
                                                ":/res/images/play.png",
                                                ":/res/images/pause.png",
                                                ":/res/images/stop.png"));

    ui->listView->addItem(new MusicPlayListItem("           曲目3:",
                                                ":/res/images/play.png",
                                                ":/res/images/pause.png",
                                                ":/res/images/stop.png"));
    ui->listView->setFont(font);
    ui->listView->setSizeHint(QSize(-1, m_height));
    ui->listView->setStrech(6, 1);
    ui->listView->setAlternatingRowColors(true);
    ui->listView->setEditTriggers(QAbstractItemView::CurrentChanged);
    ui->listView->setSelectionBackground(QColor(AppUiConfig::instance().
                                         value(AppUiConfig::MusicSelectBackground).toUInt()));

    connect(ui->listView, SIGNAL(itemClicked(MusicPlayListItem*)),
            this, SLOT(onItemClicked(MusicPlayListItem*)));
    connect(ui->listView, SIGNAL(currentItemChanged(MusicPlayListItem*,MusicPlayListItem*)),
            this, SLOT(onCurrentItemChanged(MusicPlayListItem*,MusicPlayListItem*)));
    connect(ui->listView, SIGNAL(iconClicked(MusicPlayListItem*,int)),
            this, SLOT(onIconClicked(MusicPlayListItem*,int)));
}

EducationWidget::~EducationWidget()
{
    delete ui;
}

void EducationWidget::onItemClicked(MusicPlayListItem *item)
{
    Q_UNUSED(item)
//    item->setSelected(true);
}

void EducationWidget::onCurrentItemChanged(MusicPlayListItem *current, MusicPlayListItem *previous)
{
    if(previous != NULL)
    {
        previous->setSelected(false);
        previous->setSizeHint(QSize(-1, m_height));
        previous->setPlayIcon(":/res/images/play.png");
        previous->setPauseIcon(":/res/images/pause.png");
        previous->setStopIcon(":/res/images/stop.png");
    }

    if(current != NULL)
    {
        current->setSelected(true);
        current->setSizeHint(QSize(-1, m_height * 1.5));
        current->setPlayIcon(":/res/images/play_select.png");
        current->setPauseIcon(":/res/images/pause_select.png");
        current->setStopIcon(":/res/images/stop_select.png");
    }
}

void EducationWidget::onIconClicked(MusicPlayListItem *item, int index)
{
    switch(index)
    {
    case 0:
        item->setPlayIcon(":/res/images/play_press.png");
        break;
    case 1:
        item->setPauseIcon(":/res/images/pause_press.png");
        break;
    case 2:
        item->setStopIcon(":/res/images/stop_press.png");
        break;
    default:
        break;
    }
}

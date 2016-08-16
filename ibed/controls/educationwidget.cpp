#include "educationwidget.h"
#include "ui_educationwidget.h"
#include "appuiconfig.h"
#include "musicplaylistitem.h"
#include "appsetting.h"
#include <QDir>
#include <QFileInfo>

EducationWidget::EducationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationWidget),
    m_height(0)
{
    ui->setupUi(this);

    m_font.setFamily(AppUiConfig::instance().fontFamily());
    m_font.setPixelSize(12);
    m_largeFont = m_font;
    m_largeFont.setPixelSize(24);
    m_height = QFontMetrics(m_font).height() + 15;

    ui->listView->setAlternatingRowColors(true);
    ui->listView->setEditTriggers(QAbstractItemView::CurrentChanged);

    connect(ui->listView, SIGNAL(itemClicked(MusicPlayListItem*)),
            this, SLOT(onItemClicked(MusicPlayListItem*)));
    connect(ui->listView, SIGNAL(currentItemChanged(MusicPlayListItem*,MusicPlayListItem*)),
            this, SLOT(onCurrentItemChanged(MusicPlayListItem*,MusicPlayListItem*)));
    connect(ui->listView, SIGNAL(iconClicked(MusicPlayListItem*,int)),
            this, SLOT(onIconClicked(MusicPlayListItem*,int)));


    updateEducation();
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
//        previous->setFont(m_font);
        previous->setSizeHint(QSize(-1, m_height));
        previous->setPlayIcon(":/res/images/play.png");
        previous->setPauseIcon(":/res/images/pause.png");
        previous->setStopIcon(":/res/images/stop.png");
    }

    if(current != NULL)
    {
        current->setSelected(true);
//        current->setFont(m_largeFont);
        current->setSizeHint(QSize(-1, m_height * 1.5));
        current->setPlayIcon(":/res/images/play_select.png");
        current->setPauseIcon(":/res/images/pause_select.png");
        current->setStopIcon(":/res/images/stop_select.png");
    }
}

void EducationWidget::onIconClicked(MusicPlayListItem *item, int index)
{
    QString name = item->name().trimmed();

    switch(index)
    {
    case 0:
        item->setPlayIcon(":/res/images/play_press.png");
        emit play(m_eduFiles[name]);
        break;
    case 1:
        item->setPauseIcon(":/res/images/pause_press.png");
        emit pause(m_eduFiles[name]);
        break;
    case 2:
        item->setStopIcon(":/res/images/stop_press.png");
        emit stop(m_eduFiles[name]);
        break;
    default:
        break;
    }
}

void EducationWidget::updateEducation()
{
    m_eduFiles.clear();
    ui->listView->clear();

    QDir dir(AppSetting::instance().value(AppSetting::EduAudioPath).toString());
    if(!dir.exists())
        return;

    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    int fileCount = list.count();
    if(fileCount <= 0)
        return;

    for(int i = 0; i < fileCount; ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QString suffix = fileInfo.suffix();
        if(QString::compare(suffix, QString("wav"), Qt::CaseInsensitive) == 0)
        {

            ui->listView->addItem(new MusicPlayListItem("            " + fileInfo.baseName(),
                                                ":/res/images/play.png",
                                                ":/res/images/pause.png",
                                                ":/res/images/stop.png"));

            m_eduFiles[fileInfo.baseName()] = fileInfo.absoluteFilePath();
        }
    }

    //update ui
    ui->listView->setFont(m_font);
    ui->listView->setSizeHint(QSize(-1, m_height));
    ui->listView->setStrech(6, 1);
    ui->listView->setSelectionBackground(QColor(AppUiConfig::instance().
                                         value(AppUiConfig::MusicSelectBackground).toUInt()));

}

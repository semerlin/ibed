#include "educationwidget.h"
#include "ui_educationwidget.h"
#include "appuiconfig.h"
#include "musicplaylistitem.h"

EducationWidget::EducationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationWidget)
{
    ui->setupUi(this);

    QFont font(AppUiConfig::instance().fontFamily());
    font.setPixelSize(12);
    int height = QFontMetrics(font).height() + 15;

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
    ui->listView->setSizeHint(QSize(-1, height));
    ui->listView->setStrech(6, 1);
    ui->listView->setAlternatingRowColors(true);
    ui->listView->setEditTriggers(QAbstractItemView::CurrentChanged);
}

EducationWidget::~EducationWidget()
{
    delete ui;
}

#include "inouteditlabellistdelegate.h"
#include "inoutwidget.h"
#include "ui_inoutwidget.h"
#include "util.h"
#include <QTimer>
#include "editlabellistitem.h"
#include "appuiconfig.h"
#include <QDebug>

InOutWidget::InOutWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::InOutWidget)
{
    ui->setupUi(this);
    ui->pushButtonUpload->setIcons(QStringList()
                                    << ":/res/images/upload_l.png"
                                    << ":/res/images/upload_h.png");

    ui->pushButtonUpload->setText(QT_TRANSLATE_NOOP("InOut", "上传"));
    connect(ui->pushButtonUpload, SIGNAL(pressed()), this, SLOT(onPushButtonPress()));
    connect(ui->pushButtonUpload, SIGNAL(released()), this, SLOT(onPushButtonReleased()));

    ui->labelIn->setText(QT_TRANSLATE_NOOP("InOut", "入量"));
    ui->labelOut->setText(QT_TRANSLATE_NOOP("InOut", "出量"));

    QFont font(AppUiConfig::instance().fontFamily());
    font.setPixelSize(12);
    QString name = font.family();
    int height = QFontMetrics(font).height() + 15;

    m_inDelegate = new InoutEditLabelListDelegate(ui->listViewIn);
    m_outDelegate = new InoutEditLabelListDelegate(ui->listViewOut);

    ui->listViewIn->setDelegate(m_inDelegate);
    ui->listViewIn->addItem(new EditLabelListItem("             尿液:", "100", "       ML"));
    ui->listViewIn->addItem(new EditLabelListItem("             胸液:", "100", "       ML"));
    ui->listViewIn->addItem(new EditLabelListItem("             胃液:", "100", "       ML"));
    ui->listViewIn->addItem(new EditLabelListItem("             痰液:", "100", "       ML"));
    ui->listViewIn->addItem(new EditLabelListItem("             脑髓液:", "100", "       ML"));
    ui->listViewIn->addItem(new EditLabelListItem("             纵隔引流液:", "100", "       ML"));
    ui->listViewIn->addItem(new EditLabelListItem("             创腔引流液:", "100", "       ML"));
    ui->listViewIn->addItem(new EditLabelListItem("             腹腔引流液:", "100", "       ML"));
    ui->listViewIn->addItem(new EditLabelListItem("             大便:", "100", "       g"));
    ui->listViewIn->setFont(font);
    ui->listViewIn->setSizeHint(QSize(-1, height));
    ui->listViewIn->setStrech(1, 1, 1);
    ui->listViewIn->setAlternatingRowColors(true);
    ui->listViewIn->setEditTriggers(QAbstractItemView::CurrentChanged);

    ui->listViewOut->setDelegate(m_outDelegate);
    ui->listViewOut->addItem(new EditLabelListItem("             输液液量:", "100", "       ML"));
    ui->listViewOut->addItem(new EditLabelListItem("             口服:", "100", "       ML"));
    ui->listViewOut->addItem(new EditLabelListItem("             胃肠营养液:", "100", "       ML"));
    ui->listViewOut->setFont(font);
    ui->listViewOut->setSizeHint(QSize(-1, height));
    ui->listViewOut->setStrech(1, 1, 1);
    ui->listViewOut->setAlternatingRowColors(true);
    ui->listViewOut->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listViewOut->setEditTriggers(QAbstractItemView::CurrentChanged);
}

InOutWidget::~InOutWidget()
{
    delete ui;
    delete m_inDelegate;
    delete m_outDelegate;
}

void InOutWidget::onPushButtonPress()
{
    Util::changeQssWidgetProperty(ui->pushButtonUpload, "highlight", true);
    ui->pushButtonUpload->changeToIcon(1);
}

void InOutWidget::onPushButtonReleased()
{
    Util::changeQssWidgetProperty(ui->pushButtonUpload, "highlight", false);
    ui->pushButtonUpload->changeToIcon(0);
}

void InOutWidget::onLowlightButton()
{
    ui->pushButtonUpload->changeToIcon(0);
    Util::changeQssWidgetProperty(ui->pushButtonUpload, "highlight", false);
}

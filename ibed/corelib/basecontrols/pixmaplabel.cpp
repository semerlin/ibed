#include "pixmaplabel.h"
#include "ui_pixmaplabel.h"

PixmapLabel::PixmapLabel(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::PixmapLabel)
{
    ui->setupUi(this);
}

PixmapLabel::~PixmapLabel()
{
    delete ui;
}

void PixmapLabel::setPixmap(const QPixmap &pixmap)
{
    ui->labelPic->setPixmap(pixmap);
}

void PixmapLabel::setText(const QString &text)
{
    ui->labelText->setText(text);
}

void PixmapLabel::setSpacing(int spacing)
{
    ui->verticalLayout->setSpacing(spacing);
}

void PixmapLabel::setContentsMargins(int left, int top, int right, int bottom)
{
    ui->verticalLayout->setContentsMargins(left, top, right, bottom);
}

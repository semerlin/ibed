#include "dotlabel.h"
#include "ui_dotlabel.h"
#include <QPalette>

DotLabel::DotLabel(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::DotLabel),
    m_color(Qt::white),
    m_text("")
{
    ui->setupUi(this);
    ui->labelDot->setAutoFillBackground(true);
}

DotLabel::~DotLabel()
{
    delete ui;
}

void DotLabel::setDotColor(const QColor &color)
{
    if(m_color != color)
    {
        m_color = color;
        ui->labelDot->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                    .arg(color.red())
                                    .arg(color.green())
                                    .arg(color.blue()));
    }
}

void DotLabel::setText(const QString &text)
{
    ui->labelValue->setText(text);
}

void DotLabel::setSpacing(int spacing)
{
   ui->horizontalLayout->setSpacing(spacing);
}

QColor DotLabel::dotColor() const
{
    return m_color;
}

QString DotLabel::text() const
{
    return m_text;
}

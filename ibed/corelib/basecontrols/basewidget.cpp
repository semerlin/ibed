#include "basewidget.h"
#include <QStyleOption>
#include <QStyle>
#include <QPainter>

BaseWidget::BaseWidget(QWidget *parent) :
    QWidget(parent)
{

}

void BaseWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;

    opt.init(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
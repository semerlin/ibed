#include "baselabel.h"

BaseLabel::BaseLabel(QWidget *parent) :
    QLabel(parent)
{

}

void BaseLabel::paintEvent(QPaintEvent *event)
{
    setAutoFillBackground(true);
    this->setPalette(QPalette(QPalette::Window, QColor(255, 255, 255)));

    QLabel::paintEvent(event);
}


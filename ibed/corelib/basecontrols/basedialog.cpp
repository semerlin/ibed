#include "basedialog.h"
#include <QStyleOption>
#include <QPainter>

BaseDialog::BaseDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent, f)
{

}

void BaseDialog::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);

    QStyleOption opt;

    opt.init(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

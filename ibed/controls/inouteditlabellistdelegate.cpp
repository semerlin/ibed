#include "inouteditlabellistdelegate.h"
#include <QPainter>
#include "appuiconfig.h"

InoutEditLabelListDelegate::InoutEditLabelListDelegate(QObject *parent) :
    EditLabelListDelegate(parent)
{

}

void InoutEditLabelListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        painter->save();

        int nameWidth = 0, textWidth = 0, extraWidth = 0, height = 0;
        calWidthAndHeight(option, index, nameWidth, textWidth, extraWidth, height);

        QRect nameRect = QRect(option.rect.topLeft(), QSize(nameWidth - 5, height));
        QRect textRect = QRect(option.rect.topLeft() + QPoint(nameWidth, 0) , QSize(textWidth - 5, height));
        QRect extraRect = QRect(option.rect.topLeft() + QPoint(nameWidth + textWidth, 0) , QSize(extraWidth - 5, height));

        QFont font = index.data(Qt::FontRole).value<QFont>();
        int fontHeight = QFontMetrics(font).height();
        painter->setFont(index.data(Qt::FontRole).value<QFont>());
        painter->drawText(nameRect, index.data(Qt::TextAlignmentRole).toInt(), index.data(Qt::UserRole).toString());
        QPen pen = QColor(AppUiConfig::instance().value(AppUiConfig::InoutEditColor).toUInt());
        pen.setWidth(2);
        QPen oldPen = painter->pen();
        painter->setPen(pen);
        painter->drawRect(QRect(textRect.left(), textRect.top() + (textRect.height() - fontHeight) / 2 - 3, textRect.width(), fontHeight + 6));
        painter->setPen(oldPen);
        painter->drawText(textRect, index.data(Qt::TextAlignmentRole).toInt(), index.data(Qt::DisplayRole).toString());
        painter->drawText(extraRect, index.data(Qt::TextAlignmentRole).toInt(), index.data(Qt::UserRole + 1).toString());

        painter->restore();
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}


#include "linetableview.h"
#include <QTableWidget>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QHeaderView>

class LineDelegate : public QStyledItemDelegate
{
public:
    LineDelegate(int orientation, QTableView *tableView);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QPen m_pen;
    QTableView *m_view;
    int m_orientation;
};

LineDelegate::LineDelegate(int orientation, QTableView *tableView) :
    m_view(tableView),
    m_orientation(orientation)
{
    int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());

    //get gridline pen color
    QColor gridColor = static_cast<QRgb>(gridHint);
    m_pen = QPen(gridColor, 0, tableView->gridStyle());
}

void LineDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    QStyledItemDelegate::paint(painter, option, index);

    QPen oldPen = painter->pen();

    painter->setPen(m_pen);

    if(m_orientation == Qt::Vertical)
    {
        painter->drawLine(option.rect.topLeft(), option.rect.bottomLeft());
    }
    else if(m_orientation == Qt::Horizontal)
    {
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    }
    else
    {
        painter->drawLine(option.rect.topLeft(), option.rect.bottomLeft());
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    }

    painter->setPen(oldPen);
}


LineTableView::LineTableView(QWidget *parent) :
    QTableView(parent)
{
    setShowGrid(false);
    setItemDelegate(new LineDelegate(Qt::Vertical | Qt::Horizontal, this));
}

LineTableView::LineTableView(Qt::Orientation orientation, QWidget *parent) :
    QTableView(parent)
{
    setShowGrid(false);
    setItemDelegate(new LineDelegate(orientation, this));
}

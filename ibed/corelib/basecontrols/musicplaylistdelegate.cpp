#include "musicplaylistdelegate.h"
#include "musicplaylistview.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QLineEdit>


MusicPlayListDelegate::MusicPlayListDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}


void MusicPlayListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        painter->save();

        int nameWidth = 0, textWidth = 0, extraWidth = 0, height = 0;
        calWidthAndHeight(option, index, nameWidth, textWidth, extraWidth, height);

        QRect nameRect = QRect(option.rect.topLeft(), QSize(nameWidth - 5, height));
        QRect textRect = QRect(option.rect.topLeft() + QPoint(nameWidth, 0) , QSize(textWidth - 5, height));
        QRect extraRect = QRect(option.rect.topLeft() + QPoint(nameWidth + textWidth, 0) , QSize(extraWidth - 5, height));

        painter->setFont(index.data(Qt::FontRole).value<QFont>());
        painter->drawText(nameRect, index.data(Qt::TextAlignmentRole).toInt(), index.data(Qt::UserRole).toString());
        painter->drawText(textRect, index.data(Qt::TextAlignmentRole).toInt(), index.data(Qt::DisplayRole).toString());
        painter->drawText(extraRect, index.data(Qt::TextAlignmentRole).toInt(), index.data(Qt::UserRole + 1).toString());

        painter->restore();
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget *MusicPlayListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void MusicPlayListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if(lineEdit)
    {
        lineEdit->setText(index.data(Qt::DisplayRole).toString());
    }
}

void MusicPlayListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
    if(lineEdit)
    {
        model->setData(index, lineEdit->text(), Qt::EditRole);
    }
}

void MusicPlayListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int nameWidth = 0, textWidth = 0, extraWidth = 0, height = 0;
    calWidthAndHeight(option, index, nameWidth, textWidth, extraWidth, height);

    QFont font = index.data(Qt::FontRole).value<QFont>();
    int fontHeight = QFontMetrics(font).height();

    //calucate verical offet
    int offset = 0;
    int alignment = index.data(Qt::TextAlignmentRole).toInt();
    if(alignment & Qt::AlignBottom)
    {
        offset = height - fontHeight;
    }
    else if(alignment & Qt::AlignVCenter)
    {
        offset = (height - fontHeight) / 2;
    }

    QRect decorationRect = QRect(option.rect.topLeft() + QPoint(nameWidth, offset-4), QSize(textWidth, fontHeight+8));
    editor->setGeometry(decorationRect);
    editor->setFont(font);
}

void MusicPlayListDelegate::calWidthAndHeight(const QStyleOptionViewItem &option, const QModelIndex &index,
                                              int &nameWidth, int &textWidth, int &extraWidth, int &height) const
{
    int itemHeight = -1;
    int width = -1;
    MusicPlayListView *view = qobject_cast<MusicPlayListView *>(parent());
    if(!index.data(Qt::SizeHintRole).isValid())
    {
        itemHeight = sizeHint(option, index).height();
        width = view->size().width();
    }
    else
    {
        QSize size = index.data(Qt::SizeHintRole).toSize();
        itemHeight = size.height();
        width = size.width();
    }

    if(itemHeight == -1)
        itemHeight = sizeHint(option, index).height();

    if(width == -1)
        width = view->size().width();

    int nameStrech = index.data(Qt::UserRole + 2).toInt();
    if(nameStrech < 0)
        nameStrech = 0;

    int textStrech = index.data(Qt::UserRole + 3).toInt();;
    if(textStrech < 0)
        textStrech = 0;

    int extraStrech = index.data(Qt::UserRole + 4).toInt();
    if(extraStrech < 0)
        extraStrech = 0;

    int strechSum = nameStrech + textStrech + extraStrech;
    if(strechSum == 0)
    {
        nameStrech = 1;
        textStrech = 1;
        extraStrech = 1;
        strechSum = 3;
    }

    nameWidth = width / strechSum * nameStrech;
    textWidth = width / strechSum * textStrech;
    extraWidth = width / strechSum * extraStrech;

    height = itemHeight;

}


QSize MusicPlayListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        if(!index.data(Qt::SizeHintRole).isValid())
            return QStyledItemDelegate::sizeHint(option, index);

        return index.data(Qt::SizeHintRole).toSize();
    }
    else
    {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

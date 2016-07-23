#ifndef EDITLABELLISTDELEGATE_H
#define EDITLABELLISTDELEGATE_H

#include <QStyledItemDelegate>
#include "basecontrols_global.h"

class BASECONTROLSSHARED_EXPORT EditLabelListDelegate : public QStyledItemDelegate
{
public:
    explicit EditLabelListDelegate(QObject *parent = 0);

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:
    void calWidthAndHeight(const QStyleOptionViewItem &option, const QModelIndex &index,
                           int &nameWidth, int &textWidth, int &extraWidth, int &height) const;
};

#endif // EDITLABELLISTDELEGATE_H

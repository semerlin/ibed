#ifndef EDITLABELLISTVIEW_H
#define EDITLABELLISTVIEW_H

#include "basecontrols_global.h"
#include <QListView>
#include <QStyledItemDelegate>

class EditLabelListItem;
class EditLabelListDelegate;
class EditLabelListModel;

class BASECONTROLSSHARED_EXPORT EditLabelListView : public QListView
{
    Q_OBJECT
    friend class EditLabelListItem;
    friend class EditLabelListDelegate;

public:
    EditLabelListView(QWidget *parent = 0);
    ~EditLabelListView();

public:
    void setDelegate(QStyledItemDelegate *delegate);
    void addItem(EditLabelListItem *item);
    void insertItem(int row, EditLabelListItem *item);
    void clear(void);
    EditLabelListItem *item(int row);
    void setFont(const QFont &font);
    void setSizeHint(const QSize &size);
    void setStrech(int name, int text, int extra);

private:
    EditLabelListModel *m_model;
    EditLabelListDelegate *m_delegate;
};

#endif // EDITLABELLISTVIEW_H

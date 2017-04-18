#ifndef EDITLABELLISTVIEW_H
#define EDITLABELLISTVIEW_H

#include "basecontrols_global.h"
#include <QListView>
#include <QStyledItemDelegate>

class EditLabelListItem;
class EditLabelListDelegate;
class EditLabelListModel;
class EditLabelListViewPrivate;

class BASECONTROLSSHARED_EXPORT EditLabelListView : public QListView
{
    Q_OBJECT
public:
    EditLabelListView(QWidget *parent = 0);
    ~EditLabelListView();

public:
    /**
     * @brief set item delegate
     * @param delegate - item delegate
     */
    void setDelegate(QStyledItemDelegate *delegate);

    /**
     * @brief add item to list view
     * @param item - item pointer
     */
    void addItem(EditLabelListItem *item);

    /**
     * @brief insert item to list view
     * @param row - row to insert
     * @param item - item pointer
     */
    void insertItem(int row, EditLabelListItem *item);

    /**
     * @brief clear listview
     */
    void clear(void);

    /**
     * @brief get item from list view
     * @param row - item row
     * @return item pointer
     */
    EditLabelListItem *item(int row) const;

    /**
     * @brief get all items from listview
     * @return all items
     */
    QList<EditLabelListItem *> allItems(void) const;

    /**
     * @brief set item font
     * @param font - item font
     */
    void setFont(const QFont &font);

    /**
     * @brief set item size hint
     * @param size
     */
    void setSizeHint(const QSize &size);

    /**
     * @brief set item strech
     * @param name - name strech
     * @param text - text strech
     * @param extra - extra strech
     */
    void setStrech(int name, int text, int extra);

private:
    friend class EditLabelListItem;
    friend class EditLabelListDelegate;
    EditLabelListViewPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(EditLabelListView)
};

#endif // EDITLABELLISTVIEW_H

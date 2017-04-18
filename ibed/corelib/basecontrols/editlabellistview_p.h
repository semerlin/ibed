#ifndef EDITLABELLISTVIEW_P_H
#define EDITLABELLISTVIEW_P_H

#include "basecontrols_global.h"
#include "boost/shared_ptr.hpp"

class EditLabelListView;
class EditLabelListModel;
class EditLabelListDelegate;

class BASECONTROLSSHARED_EXPORT EditLabelListViewPrivate
{
public:
    explicit EditLabelListViewPrivate(EditLabelListView *parent);

public:
    boost::shared_ptr<EditLabelListModel> m_model;
    boost::shared_ptr<EditLabelListDelegate> m_delegate;

private:
    EditLabelListView *const q_ptr;
    Q_DECLARE_PUBLIC(EditLabelListView)
};


#endif // EDITLABELLISTVIEW_P


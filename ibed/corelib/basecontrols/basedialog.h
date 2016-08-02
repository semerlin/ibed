#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include "basecontrols_global.h"
#include <QDialog>

class BASECONTROLSSHARED_EXPORT BaseDialog : public QDialog
{
public:
    explicit BaseDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~BaseDialog() {}

protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // BASEDIALOG_H

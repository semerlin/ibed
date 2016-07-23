#ifndef LABELLINEEDIT_H
#define LABELLINEEDIT_H

#include "basecontrols_global.h"
#include "basewidget.h"

namespace Ui {
class LabelLineEdit;
}

class BASECONTROLSSHARED_EXPORT LabelLineEdit : public BaseWidget
{
    Q_OBJECT

public:
    explicit LabelLineEdit(QWidget *parent = 0);
    explicit LabelLineEdit(const QString &name, const QString &text,
                           const QString &extraName, QWidget *parent = 0);
    ~LabelLineEdit();

public:
    QString text(void) const;

public slots:
    void setName(const QString &name);
    void setText(const QString &text);
    void setExtraName(const QString &name);
    void setReadOnly(void);
    void setNameVisible(bool flag);
    void setExtraNameVisible(bool flag);

private:
    Ui::LabelLineEdit *ui;
};

#endif // LABELLINEEDIT_H

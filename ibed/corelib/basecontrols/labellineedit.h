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
    /**
     * @brief set text before lineedit
     * @param name - text value
     */
    void setName(const QString &name);

    /**
     * @brief set line edit text
     * @param text - text value
     */
    void setText(const QString &text);

    /**
     * @brief set text after lineedit
     * @param name text value
     */
    void setExtraName(const QString &name);

    /**
     * @brief set lineedit readonly
     * @param flag - readonly flag
     */
    void setReadOnly(bool flag = true);

    /**
     * @brief set label visiable
     * @param flag - visiable status
     */
    void setNameVisible(bool flag);
    void setExtraNameVisible(bool flag);

    /**
     * @brief set name text and extra streach
     * @param name - streach value
     * @param text - streach value
     * @param extra - streach value
     */
    void setLayoutStrech(int name, int text, int extra);

    /**
     * @brief set spacing
     * @param spacing - spacing value
     */
    void setSpacing(int spacing);

private:
    Ui::LabelLineEdit *ui;
};

#endif // LABELLINEEDIT_H

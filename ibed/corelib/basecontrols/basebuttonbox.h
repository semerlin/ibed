#ifndef BASEBUTTONBOX_H
#define BASEBUTTONBOX_H

#include <QWidget>

namespace Ui {
class BaseButtonBox;
}

class QPushButton;

class BaseButtonBox : public QWidget
{
    Q_OBJECT

public:
    explicit BaseButtonBox(QWidget *parent = 0);
    ~BaseButtonBox();

public:
    bool addButton(const QString &name);
    void removeButton(const QString &name);
    void clearButtons(void);

public:
    const QList<QPushButton *> buttons(void) const;

private:
    QList<QPushButton *> m_buttons;
private:
    Ui::BaseButtonBox *ui;
};

#endif // BASEBUTTONBOX_H

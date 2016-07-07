#ifndef BASEBUTTONBOX_H
#define BASEBUTTONBOX_H

#include "basewidget.h"
#include <QHash>
#include <QAbstractButton>
#include <QLayout>

namespace Ui {
class BaseButtonBox;
}


class BaseButtonBox : public BaseWidget
{
    Q_OBJECT

public:
    explicit BaseButtonBox(QWidget *parent = 0);
    explicit BaseButtonBox(Qt::Orientation orientation, QWidget *parent = 0);
    ~BaseButtonBox();

public:
    /**
     * @brief set orientation
     * @param
     */
    void setOrientation(Qt::Orientation orientation);

    /**
     * @brief add a button, this is a template function,
     *        T must be inheritd QAbstractButton
     * @param button name
     */
    template <typename T>
    bool addButton(const QString &name);

    /**
     * @brief add a icon based button, this is a template function,
     *        T must be inheritd QAbstractButton
     * @param button name
     * @param icon name
     */
    template <typename T>
    bool addButton(const QString &name, const QIcon &icon);

    /**
     * @brief change button shown text
     * @param id: button position
     * @param newName: button new shown text
     */
    void changeButtonName(int id, const QString &newName);

    /**
     * @brief chang button name
     * @param origin: origin name
     * @param newName: new name
     */
    void changeButtonName(const QString &origin, const QString &newName);

    /**
     * @brief swap button position by name
     * @param first: first button
     * @param second: second button
     */
    void swapButtons(const QString &first, const QString &second);

    /**
     * @brief swap button position by position
     * @param firstId: first button position
     * @param secondId: second button position
     */
    void swapButtons(int firstId, int secondId);

    /**
     * @brief remove button by name
     * @param name: button name
     */
    void removeButton(const QString &name);

    /**
     * @brief remove button by position
     * @param id: button position based on zero
     */
    void removeButton(int id);

    /**
     * @brief remove all buttons
     */
    void clearButtons(void);

    /**
     * @brief set button layout spacing
     * @param spacing: layout spacing
     */
    void setSpacing(int spacing);

    /**
     * @brief set contents margins
     * @param left
     * @param top
     * @param right
     * @param bottom
     */
    void setContentsMargins(int left, int top, int right, int bottom);

public:
    /**
     * @brief return all buttons
     * @return
     */
    template<typename T>
    const QList<T *> buttons(void) const;

    /**
     * @brief return button by id
     * @return
     */
    template<typename T>
    T *button(int id) const;

    /**
     * @brief return button by name
     * @return
     */
    template<typename T>
    T *button(const QString &name) const;

signals:
    void buttonClicked(int id);

private slots:
    void onButtonClicked(void);

private:
    Ui::BaseButtonBox *ui;
    Qt::Orientation m_orientation;
    QLayout *m_layout;
    QHash<int, QAbstractButton *> m_buttons;
};

template <typename T>
bool BaseButtonBox::addButton(const QString &name)
{
    QAbstractButton *button = new T(this);
    if(button != NULL)
    {
        button->setText(name);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_buttons[m_buttons.count()] = button;
        m_layout->addWidget(button);
        connect(m_buttons[m_buttons.count() - 1], SIGNAL(clicked(bool)), this, SLOT(onButtonClicked()));
    }
    else
        return false;

    return true;

}

template <typename T>
bool BaseButtonBox::addButton(const QString &name, const QIcon &icon)
{
    bool ret = addButton<T>(name);
    button<T>(name)->setIcon(icon);

    return ret;
}


template <typename T>
const QList<T *> BaseButtonBox::buttons() const
{
    QList<T *> buttons;
    for(int i = 0; i < m_buttons.count(); ++i)
    {
        buttons.append(dynamic_cast<T *>(m_buttons[i]));
    }

    return buttons;
}

template <typename T>
T *BaseButtonBox::button(int id) const
{
    if(m_buttons.contains(id))
        return dynamic_cast<T *>(m_buttons[id]);
    else
        return NULL;
}

template <typename T>
T *BaseButtonBox::button(const QString &name) const
{
    for(QHash<int, QAbstractButton *>::const_iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        if(iter.value()->text() == name)
        {
            return dynamic_cast<T *>(iter.value());
        }
    }

    return NULL;
}



#endif // BaseButtonBox_H

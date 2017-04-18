#include "iconpushbutton.h"

class IconPushButtonPrivate
{
public:
    QList<QIcon> m_icons;
};

IconPushButton::IconPushButton(QWidget *parent) :
    QPushButton(parent),
    d_ptr(new IconPushButtonPrivate)
{

}

IconPushButton::~IconPushButton()
{
    delete d_ptr;
}

void IconPushButton::addIcon(const QIcon &icon)
{
    d_ptr->m_icons.append(icon);
}

void IconPushButton::addIcon(const QString &icon)
{
    d_ptr->m_icons.append(QIcon(icon));
}

void IconPushButton::setIcons(const QList<QIcon> &icons)
{
    Q_D(IconPushButton);
    d->m_icons.clear();
    d->m_icons = icons;
    if(d->m_icons.count() > 0)
        setIcon(d->m_icons.at(0));
}

void IconPushButton::setIcons(const QStringList &icons)
{
    Q_D(IconPushButton);
    d->m_icons.clear();
    foreach(const QString &name, icons)
        d->m_icons.append(QIcon(name));

    if(d->m_icons.count() > 0)
        setIcon(d->m_icons.at(0));
}

void IconPushButton::changeToIcon(int id)
{
    Q_D(IconPushButton);
    Q_ASSERT(d->m_icons.count() > id);
    setIcon(d->m_icons[id]);
}

void IconPushButton::removeIcon(int id)
{
    Q_D(IconPushButton);
    Q_ASSERT(d->m_icons.count() > id);
    d->m_icons.removeAt(id);
}

void IconPushButton::clearIcons()
{
    d_ptr->m_icons.clear();
}

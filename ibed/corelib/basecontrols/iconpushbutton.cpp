#include "iconpushbutton.h"

IconPushButton::IconPushButton(QWidget *parent) :
    QPushButton(parent)
{

}

void IconPushButton::addIcon(const QIcon &icon)
{
    m_icons.append(icon);
}

void IconPushButton::addIcon(const QString &icon)
{
    m_icons.append(QIcon(icon));
}

void IconPushButton::setIcons(const QList<QIcon> &icons)
{
    m_icons.clear();
    m_icons = icons;
    if(m_icons.count() > 0)
        setIcon(m_icons.at(0));
}

void IconPushButton::setIcons(const QStringList &icons)
{
    m_icons.clear();
    foreach(const QString &name, icons)
        m_icons.append(QIcon(name));

    if(m_icons.count() > 0)
        setIcon(m_icons.at(0));
}

void IconPushButton::changeToIcon(int id)
{
    if(m_icons.count() > id)
        setIcon(m_icons[id]);
}

void IconPushButton::removeIcon(int id)
{
    if(m_icons.count() > id)
        m_icons.removeAt(id);
}

void IconPushButton::clearIcons()
{
    m_icons.clear();
}

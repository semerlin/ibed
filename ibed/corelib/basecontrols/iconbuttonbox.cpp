#include "iconbuttonbox.h"


IconButtonBox::IconButtonBox(QWidget *parent) :
    BaseButtonBox(parent)
{

}

IconButtonBox::IconButtonBox(Qt::Orientation orientation, QWidget *parent) :
    BaseButtonBox(orientation, parent)
{

}

IconButtonBox::~IconButtonBox()
{

}

bool IconButtonBox::addButtonIcon(const QString &name, const QIcon &icon)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            m_icons[btn].append(icon);
            return true;
        }
    }

    return false;
}


bool IconButtonBox::setButtonIcons(const QString &name, const QStringList &icons)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            m_icons[btn].clear();
        }

        foreach(const QString &name, icons)
        {
            m_icons[btn].append(QIcon(name));
        }

        if(m_icons[btn].count() > 0)
            btn->setIcon(m_icons[btn].at(0));

        return true;
    }

    return false;
}


bool IconButtonBox::setButtonIcons(int id, const QStringList &icons)
{
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            m_icons[btn].clear();
        }

        foreach(const QString &name, icons)
        {
            m_icons[btn].append(QIcon(name));
        }

        if(m_icons[btn].count() > 0)
            btn->setIcon(QIcon(icons.at(0)));

        return true;
    }

    return false;
}

bool IconButtonBox::setButtonIcons(const QString &name, const QList<QIcon> &icons)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            m_icons[btn].clear();
        }

        m_icons[btn] = icons;

        if(icons.count() > 0)
            btn->setIcon(icons.at(0));

        return true;
    }

    return false;
}

bool IconButtonBox::setButtonIcons(int id, const QList<QIcon> &icons)
{
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            m_icons[btn].clear();
        }

        m_icons[btn] = icons;

        if(icons.count() > 0)
            btn->setIcon(icons.at(0));

        return true;
    }

    return false;
}

void IconButtonBox::changeToIcon(const QString &name, int num)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            if(m_icons[btn].count() > num)
                btn->setIcon(m_icons[btn].at(num));
        }
    }
}

void IconButtonBox::changeToIcon(int id, int num)
{
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            if(m_icons[btn].count() > num)
                btn->setIcon(m_icons[btn].at(num));
        }
    }
}

void IconButtonBox::changeToIcon(const QString &name, const QIcon &icon)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        btn->setIcon(icon);
    }
}

void IconButtonBox::changeToIcon(int id, const QIcon &icon)
{
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        btn->setIcon(icon);
    }
}

void IconButtonBox::removeIcon(int id, int num)
{
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            if(m_icons[btn].count() > num)
                m_icons[btn].removeAt(num);
        }
    }
}

void IconButtonBox::removeIcon(const QString &name, int num)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            if(m_icons[btn].count() > num)
                m_icons[btn].removeAt(num);
        }
    }
}

void IconButtonBox::clearIcons()
{
    m_icons.clear();
}

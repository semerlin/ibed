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

void IconButtonBox::setButtonIcon(const QString &name, const QStringList &icons)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            m_icons[btn].clear();
            m_icons[btn] = icons;
        }
        else
            m_icons[btn] = icons;

        if(icons.count() > 0)
            btn->setIcon(QIcon(icons.at(0)));
    }
}

void IconButtonBox::setButtonIcon(int id, const QStringList &icons)
{
    QAbstractButton *btn = button<QAbstractButton>(id);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            m_icons[btn].clear();
            m_icons[btn] = icons;
        }
        else
            m_icons[btn] = icons;

        if(icons.count() > 0)
            btn->setIcon(QIcon(icons.at(0)));

    }
}

void IconButtonBox::changeToIcon(const QString &name, int num)
{
    QAbstractButton *btn = button<QAbstractButton>(name);
    if(btn != NULL)
    {
        if(m_icons.contains(btn))
        {
            if(m_icons[btn].count() > num)
                btn->setIcon(QIcon(m_icons[btn].at(num)));
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
                btn->setIcon(QIcon(m_icons[btn].at(num)));
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

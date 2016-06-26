#include <QPushButton>
#include "basebuttonbox.h"
#include "ui_basebuttonbox.h"
#include "boost/foreach.hpp"

BaseButtonBox::BaseButtonBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseButtonBox)
{
    ui->setupUi(this);
}

BaseButtonBox::~BaseButtonBox()
{
    delete ui;
}

void BaseButtonBox::clearButtons()
{
    for(QList<QPushButton *>::iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        if((*iter) != NULL)
            delete (*iter);
    }

    m_buttons.clear();
}

bool BaseButtonBox::addButton(const QString &name)
{
    QPushButton *button = new QPushButton(name, this);
    if(button != NULL)
    {
        m_buttons.append(button);
    }
    else
        return false;

    return true;

}

void BaseButtonBox::removeButton(const QString &name)
{
    BOOST_FOREACH(QPushButton *button, m_buttons)
    {
        if(button->text() == name)
        {
            m_buttons.removeOne(button);
            delete button;
        }
    }
}


const QList<QPushButton *> BaseButtonBox::buttons() const
{
    return m_buttons;
}

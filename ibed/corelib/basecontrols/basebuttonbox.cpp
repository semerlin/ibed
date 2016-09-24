#include "basebuttonbox.h"
#include "ui_basebuttonbox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

BaseButtonBox::BaseButtonBox(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::BaseButtonBox),
    m_orientation(Qt::Horizontal)

{
    ui->setupUi(this);
    if(m_orientation == Qt::Horizontal)
        m_layout = new QHBoxLayout;
    else
        m_layout = new QVBoxLayout;

    ui->verticalLayout->addLayout(m_layout);

}

BaseButtonBox::BaseButtonBox(Qt::Orientation orientation, QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::BaseButtonBox),
    m_orientation(orientation)
{
    ui->setupUi(this);
    if(m_orientation == Qt::Horizontal)
        m_layout = new QHBoxLayout;
    else
        m_layout = new QVBoxLayout;

    ui->verticalLayout->addLayout(m_layout);

}


BaseButtonBox::~BaseButtonBox()
{
    delete ui;
}

void BaseButtonBox::setOrientation(Qt::Orientation orientation)
{
    if(orientation == m_orientation)
        return ;

    m_orientation = orientation;
    if(m_layout)
    {
        //remove widget
        for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
            iter != m_buttons.end(); ++iter)
        {
            m_layout->removeWidget(iter.value());
        }

        delete m_layout;
    }

    if(m_orientation == Qt::Horizontal)
        m_layout = new QHBoxLayout(this);
    else
        m_layout = new QVBoxLayout(this);

    ui->verticalLayout->addLayout(m_layout);
    //add widget
    for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        m_layout->addWidget(iter.value());
    }
}



void BaseButtonBox::clearButtons()
{
    for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        m_layout->removeWidget(iter.value());
        disconnect(iter.value(), SIGNAL(clicked(bool)), this, SLOT(onButtonClicked()));
        if(iter.value() != NULL)
            delete iter.value();
    }

    m_buttons.clear();
}

void BaseButtonBox::setSpacing(int spacing)
{
    m_layout->setSpacing(spacing);
}

void BaseButtonBox::setContentsMargins(int left, int top, int right, int bottom)
{
   m_layout->setContentsMargins(left, top, right, bottom);
}



void BaseButtonBox::changeButtonName(int id, const QString &newName)
{
    if(m_buttons.contains(id))
        m_buttons[id]->setText(newName);
}


void BaseButtonBox::changeButtonName(const QString &origin, const QString &newName)
{
    for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        if(iter.value()->text() == origin)
        {
            iter.value()->setText(newName);
            break;
        }
    }
}


void BaseButtonBox::swapButtons(const QString &src, const QString &dest)
{
    int srcPos = -1, destPos = -1;
    QAbstractButton *srcButton, *destButton;

    //find button pos
    for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        if(iter.value()->text() == src)
        {
            srcButton = iter.value();
            srcPos = iter.key();
        }

        if(iter.value()->text() == dest)
        {
            destButton = iter.value();
            destPos = iter.key();
        }

    }

    //swap button
    if((srcPos != -1) && (destPos != -1))
    {
        m_buttons.remove(srcPos);
        m_buttons.remove(destPos);
        m_buttons[srcPos] = destButton;
        m_buttons[destPos] = srcButton;
    }
    else
        return ;

    //refresh button widget
    for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        m_layout->removeWidget(iter.value());
    }

    for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        m_layout->addWidget(iter.value());
    }

}


void BaseButtonBox::swapButtons(int srcId, int destId)
{
    if((m_buttons.contains(srcId)) && (m_buttons.contains(destId)))
    {
        QAbstractButton *srcButton = m_buttons[srcId];
        QAbstractButton *destButton = m_buttons[destId];

        m_buttons.remove(srcId);
        m_buttons.remove(destId);

        m_buttons[srcId] = destButton;
        m_buttons[destId] = srcButton;

        //refresh button widget
        for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
            iter != m_buttons.end(); ++iter)
        {
            m_layout->removeWidget(iter.value());
        }

        for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
            iter != m_buttons.end(); ++iter)
        {
            m_layout->addWidget(iter.value());
        }
    }
}


void BaseButtonBox::removeButton(const QString &name)
{
    for(QHash<int, QAbstractButton *>::iterator iter = m_buttons.begin();
        iter != m_buttons.end(); ++iter)
    {
        if(iter.value()->text() == name)
        {
            m_layout->removeWidget(iter.value());
            disconnect(iter.value(), SIGNAL(clicked(bool)), this, SLOT(onButtonClicked()));
            delete iter.value();
            m_buttons.remove(iter.key());
            break;
        }
    }

}


void BaseButtonBox::removeButton(int id)
{
    if(m_buttons.contains(id))
    {
        m_layout->removeWidget(m_buttons[id]);
        disconnect(m_buttons[id], SIGNAL(clicked(bool)), this, SLOT(onButtonClicked()));
        delete m_buttons[id];
        m_buttons.remove(id);
    }
}

void BaseButtonBox::onButtonClicked()
{
    QAbstractButton *btn = qobject_cast<QAbstractButton *>(sender());
    if(btn != NULL)
        emit buttonClicked(m_buttons.key(btn));
}


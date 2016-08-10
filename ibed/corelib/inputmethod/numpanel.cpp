#include "numipmethod.h"
#include "numpanel.h"
#include "ui_numpanel.h"
#include <QSignalMapper>
#include <QDebug>

#ifdef TARGET_IMX

NumPanel::NumPanel(NumIPMethod *method, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumPanel),
    m_mapper(new QSignalMapper(this)),
    m_method(method),
    m_lastFocusWidget(NULL)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(onFocusChanged(QWidget*,QWidget*)));

    QList<QPushButton *> allButtons = findChildren<QPushButton *>();
    for(QList<QPushButton *>::iterator iter = allButtons.begin();
        iter != allButtons.end(); ++iter)
    {
        bool ok = false;
        int id = (*iter)->objectName().remove("pushButton_").toInt(&ok);
        if(ok)
        {
            m_mapper->setMapping((*iter), id);
            connect((*iter), SIGNAL(clicked()), m_mapper, SLOT(map()));
        }
    }

    connect(m_mapper, SIGNAL(mapped(int)), this, SIGNAL(keyPressed(int)));

    if(m_method != NULL)
        connect(this, SIGNAL(keyPressed(int)), m_method, SLOT(processKey(int)));

}

NumPanel::~NumPanel()
{
    delete ui;
}

bool NumPanel::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::WindowActivate:
        if(m_lastFocusWidget != NULL)
            m_lastFocusWidget->activateWindow();
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

void NumPanel::onFocusChanged(QWidget *old, QWidget *now)
{
    Q_UNUSED(old)

    if(now != NULL && !this->isAncestorOf(now))
        m_lastFocusWidget = now;
}

#endif



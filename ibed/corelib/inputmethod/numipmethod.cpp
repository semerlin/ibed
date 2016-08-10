#include "numpanel.h"
#include "numipmethod.h"
#include <QPointer>
#include <QKeyEvent>
#include <QWidget>

#ifdef TARGET_IMX

NumIPMethod::NumIPMethod(QWidget *parent) :
    m_panel(new NumPanel(this, parent))
{
}

NumIPMethod::~NumIPMethod()
{
    delete m_panel;
}

void NumIPMethod::updateHandler(int type)
{
    switch(type)
    {
    case QWSInputMethod::FocusIn:
        if(m_panel->isHidden())
            m_panel->show();
        break;
    case QWSInputMethod::FocusOut:
        m_panel->hide();
        break;
    default:
        break;
    }
}

void NumIPMethod::move(int x, int y)
{
    m_panel->move(x, y);
}

void NumIPMethod::resize(int width, int height)
{
    m_panel->resize(width, height);
}

void NumIPMethod::setGeometry(int x, int y, int w, int h)
{
    m_panel->setGeometry(x, y, w, h);
}

void NumIPMethod::processKey(int key)
{
    QPointer<QWidget> w = qApp->focusWidget();

    //no active widget
    if(w == NULL)
        return;

    switch(key)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        sendCommitString(QString::number(key));
        break;
    case 10:
        sendCommitString(".");
        break;
    case 11:
        processSpecial(Qt::Key_Left);
        break;
    case 12:
        processSpecial(Qt::Key_Right);
        break;
    case 13:
        processSpecial(Qt::Key_Backspace);
        break;
    case 255:
        m_panel->hide();
        break;
    default:
        break;
    }
}

void NumIPMethod::processSpecial(int id)
{
    QPointer<QWidget> w = qApp->focusWidget();

    //check active widget
    if(w == NULL)
        return;

    QKeyEvent keyPress(QEvent::KeyPress, id, Qt::NoModifier, QString());
    QApplication::sendEvent(w, &keyPress);
}

#endif

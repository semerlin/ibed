#include "numipmethod.h"
#include <QPointer>
#include <QKeyEvent>
#include <QWidget>

NumIPMethod::NumIPMethod()
{

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
        processSpecial(Qt::Key_Space);
        break;
    case 12:
        processSpecial(Qt::Key_Left);
        break;
    case 13:
        processSpecial(Qt::Key_Right);
        break;
    case 14:
        processSpecial(Qt::Key_Backspace);
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


#include "baseapplication.h"
#include <QKeyEvent>


BaseApplication::BaseApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{

}

bool BaseApplication::notify(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        emit keyPressed(keyEvent->key());
     }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        emit mousePressed(mouseEvent->buttons());
    }
    return QApplication::notify(obj, event);
}

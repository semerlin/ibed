#ifndef BASEAPPLICATION_H
#define BASEAPPLICATION_H

#include "mainmodule_global.h"
#include <QApplication>

class MAINMODULESHARED_EXPORT BaseApplication : public QApplication
{
    Q_OBJECT
public:
    BaseApplication(int &argc, char **argv);

public:
    bool notify(QObject *obj, QEvent *event);

signals:
    void keyPressed(int key);
    void mousePressed(const Qt::MouseButtons &buttons);
};

#endif // BASEAPPLICATION_H

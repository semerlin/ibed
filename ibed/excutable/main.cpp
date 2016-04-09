#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QImageReader>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //启动界面
    QPixmap pixmap("res/a.bmp");
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();

    Widget w;
    w.show();

    return app.exec();
}

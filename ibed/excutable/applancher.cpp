#include "applancher.h"
#include <QPixmap>
#include <QSplashScreen>
#include <QApplication>
#include "mainwidget.h"

AppLancher &AppLancher::instance()
{
   static AppLancher m_appLancher;
   return m_appLancher;
}

int AppLancher::run(int argc, char **argv)
{
   static QApplication *app = new QApplication(argc, argv);
//    static QApplication app(argc, argv);

   MainWidget w;
   w.show();
    //startup window
//    QPixmap pixmap("res/a.bmp");
//    QSplashScreen splash(pixmap);
//    splash.show();
//    app->processEvents();

    return app->exec();
}

AppLancher::AppLancher()
{

}


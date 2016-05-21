#include "applancher.h"
#include <QApplication>
#include "mainwidget.h"
//#include "powermange.h"
//#include "backlight.h"

int main(int argc, char *argv[])
{
    return AppLancher::instance().run(argc, argv);
//    QApplication app(argc, argv);

//     //main window
//    MainWidget w;
//    w.show();

//    Backlight::instance().setValue(100);

//    PowerMange::instance().addDevice(&Backlight::instance());
//    PowerMange::instance().setIdleInterval(5);
//    PowerMange::instance().setSuspendInterval(2);

//    PowerMange::instance().run();
//    for(int i = 0; i < 100; i += 5)
//        Backlight::instance().setValue(i);


//    return app.exec();
}

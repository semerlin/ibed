#include "ibedlancher.h"
#include <QApplication>

IBedLancher::IBedLancher()
{

}



IBedLancher &IBedLancher::instance()
{
   static IBedLancher m_lancher;
   return m_lancher;
}

int IBedLancher::run(int argc, char **argv)
{
    QApplication app(argc, argv);

    static LanchWidget widget;
    static ModuleManger manger;
    manger.addModule(&HardwareModule::instance());
    BaseAppLancher lancher(&widget, &manger);
    lancher.run(argc, argv);

    return app.exec();
}

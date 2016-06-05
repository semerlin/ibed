#include <QApplication>
#include "baseapplancher.h"
#include "lanchwidget.h"
#include "modulemanger.h"
#include "hardwaremodule.h"
#include "iapplancherwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LanchWidget widget;
    ModuleManger manger;
    HardwareModule *module = new HardwareModule("Hardware");
    manger.addModule(module);
    delete module;
    manger.unloadModules();
//    manger.addModule(&HardwareModule::instance());
//    BaseAppLancher lancher(&widget, &manger);
//    lancher.run(argc, argv);

    return app.exec();
}

#include "baseapplancher.h"
#include <QApplication>

BaseAppLancher::BaseAppLancher()
{

}

int BaseAppLancher::run(int argc, char **argv)
{
    QApplication app(argc, argv);

    return app.exec();
}

//void BaseAppLancher::addStep(IAppLancher::stepFunc func)
//{

//}



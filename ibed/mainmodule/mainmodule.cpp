#include "mainmodule.h"
#include "mainwidget.h"


MainModule::MainModule()
{
}

bool MainModule::initialize()
{
    MainWidget *widget = new MainWidget;
    widget->show();
}

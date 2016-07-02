#include "mainwidget.h"
#include "mainmodule.h"

MainModule::MainModule() :
    m_mainWidget(new MainWidget)
{
}

bool MainModule::initialize()
{
    m_mainWidget->show();

    return true;
}

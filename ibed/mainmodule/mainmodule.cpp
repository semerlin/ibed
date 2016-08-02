#include "mainwidget.h"
#include "standbywidget.h"
#include "calldialog.h"
#include "progressdialog.h"
#include "mainmodule.h"

MainModule::MainModule() :
    m_mainWidget(new MainWidget),
    m_standbyWidget(new StandbyWidget),
    m_callDialog(new CallDialog),
    m_progressDialog(new ProgressDialog)
{
}

bool MainModule::initialize()
{
    m_mainWidget->show();
//    m_standbyWidget->show();

//    m_callDialog->show();
//    m_progressDialog->show();
    return true;
}

#include "mainwidget.h"
#include "standbywidget.h"
#include "calldialog.h"
#include "progressdialog.h"
#include "uimodule.h"
#include <QResource>

UiModule::UiModule(const QString &name) :
    BaseAppModule(name)
{

}

UiModule::~UiModule()
{

}

bool UiModule::load(const QVariant &val)
{
    Q_UNUSED(val)
    //register resource
    QResource::registerResource("./resource/ui/res.rcc");


    m_mainWidget =new MainWidget;
    m_standbyWidget =new StandbyWidget;
    m_callDialog =new CallDialog;
    m_progressDialog =new ProgressDialog;

    return true;
}

void UiModule::unload()
{
    delete m_progressDialog;
    delete m_callDialog;
    delete m_standbyWidget;
    delete m_mainWidget;
}

MainWidget *UiModule::mainWidget() const
{
   return m_mainWidget;
}

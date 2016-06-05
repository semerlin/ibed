#include "baseappmodule.h"



BaseAppModule::BaseAppModule(const QString &name) :
    m_name(name),
    m_error("No error"),
    m_isLoaded(false),
    m_val(QVariant(QVariant::Invalid))
{
}


BaseAppModule::~BaseAppModule()
{
    if(m_isLoaded)
    {
        unload();
    }

//    emit deleted();
}

bool BaseAppModule::load(const QVariant &val)
{
    m_val = val;
    m_isLoaded = true;

    emit message(tr("load base application module"));

    return true;
}


bool BaseAppModule::isLoaded() const
{
    return m_isLoaded;
}

void BaseAppModule::unload()
{

}

void BaseAppModule::reload()
{
    if(m_isLoaded)
    {
        unload();
    }

    load(m_val);
}

void BaseAppModule::setName(const QString &name)
{
    m_name = name;
}

QString BaseAppModule::name() const
{
    return m_name;
}

QString BaseAppModule::error() const
{
    return m_error;
}

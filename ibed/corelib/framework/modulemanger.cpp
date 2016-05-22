#include "modulemanger.h"
#include "boost/foreach.hpp"
#include "log4qt/logger.h"

LOG4QT_DECLARE_STATIC_LOGGER(log,SimpleStateMachine)

ModuleManger::ModuleManger() :
    m_error("No error")
{

}

ModuleManger::~ModuleManger()
{
    unloadedModules();
    m_error = "No error";
}

void ModuleManger::addModule(IAppModule *module)
{
    Q_ASSERT_X(module != NULL, "ModuleManger::addModule",
               "module can\'t be NULL!");

    m_modules.insert(module);
    m_moduleWithNames[module->name()] = module;

    emit moduleChanged(module, MODULE_ADD);
}

void ModuleManger::addModules(const QSet<IAppModule *> &modules)
{
    BOOST_FOREACH(IAppModule *module, modules)
    {
        m_modules.insert(module);
        m_moduleWithNames[module->name()] = module;

        emit moduleChanged(module, MODULE_ADD);
    }
}

void ModuleManger::setModules(const QSet<IAppModule *> &modules)
{
    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        emit moduleChanged(module, MODULE_REMOVE);
    }

    m_modules.clear();
    m_moduleWithNames.clear();
    m_modules = modules;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        m_moduleWithNames[module->name()] = module;

        emit moduleChanged(module, MODULE_ADD);
    }
}

void ModuleManger::removeModule(IAppModule *module)
{
    m_modules.remove(module);
    m_moduleWithNames.remove(module->name());

    emit moduleChanged(module, MODULE_REMOVE);
}

void ModuleManger::removeModule(const QString &name)
{
    if(m_moduleWithNames.contains(name))
    {
        IAppModule *module = m_moduleWithNames[name];
        m_modules.remove(module);
        m_moduleWithNames.remove(name);

        emit moduleChanged(module, MODULE_REMOVE);
    }
}

QSet<IAppModule *> ModuleManger::modules() const
{
    return m_modules;
}

QStringList ModuleManger::moduleNames() const
{
    QStringList ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        ret << module->name();
    }

    return ret;
}

QSet<IAppModule *> ModuleManger::loadedModules() const
{
    QSet<IAppModule *> ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(module->isLoaded())
            ret.insert(module);
    }

    return ret;
}

QStringList ModuleManger::loadedModuleNames() const
{
    QStringList ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(module->isLoaded())
            ret << module->name();
    }

    return ret;

}

QSet<IAppModule *> ModuleManger::unloadedModules() const
{
    QSet<IAppModule *> ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(!module->isLoaded())
            ret.insert(module);
    }

    return ret;

}

QStringList ModuleManger::unloadedModuleNames() const
{
    QStringList ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(!module->isLoaded())
            ret << module->name();
    }

    return ret;

}

bool ModuleManger::loadModule(const QString &name, const QVariant &val)
{
    bool ret = false;

    if(m_moduleWithNames.contains(name))
    {
        if(!m_moduleWithNames[name]->isLoaded())
        {
            ret = m_moduleWithNames[name]->load(val);
            if(!ret)
            {
                m_error = m_moduleWithNames[name]->error();
                emit moduleChanged(m_moduleWithNames[name], MODULE_LOAD_FAILED);
            }
            else
                emit moduleChanged(m_moduleWithNames[name], MODULE_LOAD);
        }
    }

    return ret;
}

bool ModuleManger::loadModules(const QVariant &val)
{
    bool ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(!module->isLoaded())
        {
            ret = module->load(val);
            if(!ret)
            {
                m_error = module->error();
                emit moduleChanged(module, MODULE_LOAD_FAILED);
                break;
            }
            else
                emit moduleChanged(module, MODULE_LOAD);
        }
    }

    return ret;
}


bool ModuleManger::reloadModule(const QString &name, const QVariant &val)
{
    bool ret = false;

    if(m_moduleWithNames.contains(name))
    {
        if(m_moduleWithNames[name]->isLoaded())
            m_moduleWithNames[name]->unload();

        ret = m_moduleWithNames[name]->load(val);
        if(!ret)
        {
            m_error = m_moduleWithNames[name]->error();
            emit moduleChanged(m_moduleWithNames[name], MODULE_LOAD_FAILED);
        }
        else
            emit moduleChanged(m_moduleWithNames[name], MODULE_RELOAD);
    }

    return ret;
}

bool ModuleManger::reloadModules(const QVariant &val)
{
    bool ret = false;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(module->isLoaded())
            module->unload();

        ret = module->load(val);
        if(!ret)
        {
            m_error = module->error();
            emit moduleChanged(module, MODULE_LOAD_FAILED);
            break;
        }
        else
            emit moduleChanged(module, MODULE_RELOAD);
    }

    return ret;
}

void ModuleManger::unloadModule(const QString &name)
{
    if(m_moduleWithNames.contains(name))
    {
        if(m_moduleWithNames[name]->isLoaded())
        {
            m_moduleWithNames[name]->unload();
            emit moduleChanged(m_moduleWithNames[name], MODULE_UNLOAD);
        }
    }
}

void ModuleManger::unloadModules()
{
    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(module->isLoaded())
        {
            module->unload();
            emit moduleChanged(module, MODULE_UNLOAD);
        }
    }
}

QString ModuleManger::error() const
{
    return m_error;
}

void ModuleManger::onLoadModule(const QString &name, const QVariant &val)
{
    bool ret = false;

    if(m_moduleWithNames.contains(name))
    {
        if(!m_moduleWithNames[name]->isLoaded())
        {
            ret = m_moduleWithNames[name]->load(val);
            if(!ret)
            {
                m_error = m_moduleWithNames[name]->error();
                emit moduleChanged(m_moduleWithNames[name], MODULE_LOAD_FAILED);
            }
            else
                emit moduleChanged(m_moduleWithNames[name], MODULE_LOAD);
        }
    }
}

void ModuleManger::onLoadModules(const QVariant &val)
{
    bool ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(!module->isLoaded())
        {
            ret = module->load(val);
            if(!ret)
            {
                m_error = module->error();
                emit moduleChanged(module, MODULE_LOAD_FAILED);
                break;
            }
            else
                emit moduleChanged(module, MODULE_LOAD);
        }
    }
}



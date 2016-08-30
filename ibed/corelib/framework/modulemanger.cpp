#include "modulemanger.h"
#include "boost/foreach.hpp"
#include "log4qt/logger.h"

LOG4QT_DECLARE_STATIC_LOGGER(log, ModuleManger)


ModuleManger::ModuleManger() :
    m_error("No error"),
    m_isOutMainThread(false)
{
    qRegisterMetaType<ModuleManger::MODULE_STATUS>("ModuleManger::MODULE_STATUS");
}

ModuleManger::~ModuleManger()
{
    unloadedModules();
}

void ModuleManger::addModule(IAppModule *module)
{
    Q_ASSERT_X(module != NULL, "ModuleManger::addModule",
               "module can\'t be NULL!");

    m_modules.append(module);
    m_moduleWithNames[module->name()] = module;

    connect(module, SIGNAL(destroyed(QObject*)),
            this, SLOT(onModuleDestroyed(QObject*)), Qt::DirectConnection);
    emit moduleChanged(module, MODULE_ADD);
}

void ModuleManger::addModules(const QList<IAppModule *> &modules)
{
    BOOST_FOREACH(IAppModule *module, modules)
    {
        m_modules.append(module);
        m_moduleWithNames[module->name()] = module;

        connect(module, SIGNAL(destroyed(QObject*)),
                this, SLOT(onModuleDestroyed(QObject*)), Qt::DirectConnection);
        emit moduleChanged(module, MODULE_ADD);
    }
}

void ModuleManger::setModules(const QList<IAppModule *> &modules)
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

        connect(module, SIGNAL(destroyed(QObject*)),
                this, SLOT(onModuleDestroyed(QObject*)), Qt::DirectConnection);
        emit moduleChanged(module, MODULE_ADD);
    }
}

void ModuleManger::removeModule(IAppModule *module)
{
    m_modules.removeOne(module);
    m_moduleWithNames.remove(module->name());

    disconnect(module, SIGNAL(destroyed(QObject*)),
               this, SLOT(onModuleDestroyed(QObject*)));
    emit moduleChanged(module, MODULE_REMOVE);
}

void ModuleManger::removeModule(const QString &name)
{
    if(m_moduleWithNames.contains(name))
    {
        IAppModule *module = m_moduleWithNames[name];
        m_modules.removeOne(module);
        m_moduleWithNames.remove(name);

        disconnect(module, SIGNAL(destroyed(QObject*)),
                   this, SLOT(onModuleDestroyed(QObject*)));
        emit moduleChanged(module, MODULE_REMOVE);
    }
}

QList<IAppModule *> ModuleManger::modules() const
{
    return m_modules;
}

IAppModule *ModuleManger::module(const QString &name)
{
    if(m_moduleWithNames.contains(name))
        return m_moduleWithNames[name];

    return NULL;
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

QList<IAppModule *> ModuleManger::loadedModules() const
{
    QList<IAppModule *> ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(module->isLoaded())
            ret.append(module);
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

QList<IAppModule *> ModuleManger::unloadedModules() const
{
    QList<IAppModule *> ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(module)
        {
            if(!module->isLoaded())
                ret.append(module);
        }
    }

    return ret;

}

QStringList ModuleManger::unloadedModuleNames() const
{
    QStringList ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(module)
        {
            if(!module->isLoaded())
                ret << module->name();
        }
    }

    return ret;

}

bool ModuleManger::loadModule(const QString &name, const QVariant &val)
{
    bool ret = false;

    if(m_moduleWithNames.contains(name))
    {
        if(m_isOutMainThread)
        {
            if(!m_moduleWithNames[name]->canRunInThread())
                return false;
        }

        if(!m_moduleWithNames[name]->isLoaded())
        {
            emit moduleChanged(m_moduleWithNames[name], MODULE_LOADING);
            ret = m_moduleWithNames[name]->load(val);
            if(!ret)
            {
                m_error = m_moduleWithNames[name]->error();
                log()->info(tr("load module '%1' failed-%2").arg(name).arg(m_error));
                emit moduleChanged(m_moduleWithNames[name], MODULE_LOAD_FAILED);
            }
            else
            {
                log()->info(tr("load module '%1'"));
                emit moduleChanged(m_moduleWithNames[name], MODULE_LOADED);
            }
        }
    }

    return ret;
}

bool ModuleManger::loadModules(const QVariant &val)
{
    bool ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(m_isOutMainThread)
        {
            if(!module->canRunInThread())
                continue;
        }

        if(!module->isLoaded())
        {
            emit moduleChanged(module, MODULE_LOADING);
            ret = module->load(val);
            if(!ret)
            {
                m_error = module->error();
                log()->info(tr("load module '%1' failed-%2").arg(module->name()).arg(m_error));
                emit moduleChanged(module, MODULE_LOAD_FAILED);
                break;
            }
            else
            {
                log()->info(tr("load module '%1'").arg(module->name()));
                emit moduleChanged(module, MODULE_LOADED);
            }
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

        if(m_isOutMainThread)
        {
            if(!m_moduleWithNames[name]->canRunInThread())
                return false;
        }

        emit moduleChanged(m_moduleWithNames[name], MODULE_RELOADING);
        ret = m_moduleWithNames[name]->load(val);
        if(!ret)
        {
            m_error = m_moduleWithNames[name]->error();
            emit moduleChanged(m_moduleWithNames[name], MODULE_LOAD_FAILED);
        }
        else
            emit moduleChanged(m_moduleWithNames[name], MODULE_RELOADED);
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

        if(m_isOutMainThread)
        {
            if(!module->canRunInThread())
                continue;
        }

        emit moduleChanged(module, MODULE_RELOADING);
        ret = module->load(val);
        if(!ret)
        {
            m_error = module->error();
            emit moduleChanged(module, MODULE_LOAD_FAILED);
            break;
        }
        else
            emit moduleChanged(module, MODULE_RELOADED);
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

void ModuleManger::setOutMainThread(bool flag)
{
    m_isOutMainThread = flag;
}

bool ModuleManger::isOutMainThread() const
{
    return m_isOutMainThread;
}

QString ModuleManger::error() const
{
    return m_error;
}

void ModuleManger::moduleChanging(IAppModule *module, ModuleManger::MODULE_STATUS status)
{
    emit moduleChanged(module, status);
}

void ModuleManger::onLoadModule(const QString &name, const QVariant &val)
{
    bool ret = false;

    if(m_moduleWithNames.contains(name))
    {
        if(m_isOutMainThread)
        {
            if(!m_moduleWithNames[name]->canRunInThread())
            {
                return ;
            }
        }

        if(!m_moduleWithNames[name]->isLoaded())
        {
            emit moduleChanged(m_moduleWithNames[name], MODULE_LOADING);
            ret = m_moduleWithNames[name]->load(val);
            if(!ret)
            {
                m_error = m_moduleWithNames[name]->error();
                log()->info(tr("load module '%1' failed-%2").arg(name).arg(m_error));
                emit moduleChanged(m_moduleWithNames[name], MODULE_LOAD_FAILED);
            }
            else
            {
                log()->info(tr("load module '%1'").arg(name));
                emit moduleChanged(m_moduleWithNames[name], MODULE_LOADED);
            }
        }
    }
}

void ModuleManger::onLoadModules(const QVariant &val)
{
    bool ret;

    BOOST_FOREACH(IAppModule *module, m_modules)
    {
        if(m_isOutMainThread)
        {
            if(!module->canRunInThread())
            {
                continue;
            }
        }

        if(!module->isLoaded())
        {
            emit moduleChanged(module, MODULE_LOADING);
            ret = module->load(val);
            if(!ret)
            {
                m_error = module->error();
                log()->info(tr("load module '%1' failed-%2").arg(module->name()).arg(m_error));
                emit moduleChanged(module, MODULE_LOAD_FAILED);
                break;
            }
            else
            {
                log()->info(tr("load module '%1'").arg(module->name()));
                emit moduleChanged(module, MODULE_LOADED);
            }
        }
    }

    if(ret)
        emit moduleChanged(NULL, MODULE_LOAD_FINISHED);
}

void ModuleManger::onModuleDestroyed(QObject *module)
{
    if(module)
        m_modules.removeOne(reinterpret_cast<IAppModule *>(module));
}


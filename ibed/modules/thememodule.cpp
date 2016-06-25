#include <QStringList>
#include "thememodule.h"
#include "qssloader.h"
#include <QDir>
#include <QPair>
#include "appuiconfig.h"
#include "util.h"


ThemeModule::ThemeModule(const QString &name) :
    BaseAppModule(name),
    m_loader(NULL)
{
    m_themes.clear();
}

ThemeModule::~ThemeModule()
{
    unload();
}

bool ThemeModule::load(const QVariant &val)
{
    Q_UNUSED(val)

    bool ret = false;

    if(m_loader == NULL)
    {
        m_loader = new QssLoader;
        if(m_loader == NULL)
        {
            m_isLoaded = false;
            m_error = QObject::tr("No enough memory space!");
            return false;
        }
    }

    //make pair qss file and its short name, for example
    //"C:/test/default.qss" and "default"
    QStringList qss = m_loader->findAllQss(AppUiConfig::instance().qssPath());
    foreach(const QString &name, qss)
    {
        QString fileName, shortCut;
        int splash = name.lastIndexOf(QDir::separator());
        if(splash == -1)
            fileName = name;
        else
        {
            fileName = name.mid(splash + 1);
        }

        m_themes[Util::instance().fileName(fileName)] = name;
    }

    QString shortCut = Util::instance().fileName(
                AppUiConfig::instance().defaultQss());

    //load default qss
    if(m_themes.contains(shortCut))
        ret = m_loader->loadQss(m_themes[shortCut]);
    else
        ret = m_loader->loadQss(m_themes.begin().value());

    if(ret)
        m_isLoaded = true;

    return ret;
}

void ThemeModule::unload()
{
    if(m_loader)
    {
        m_themes.clear();
        delete m_loader;
    }

    m_isLoaded = false;
    m_error = tr("No error");
}

bool ThemeModule::canRunInThread() const
{
    return false;
}

QStringList ThemeModule::themes()
{
    QStringList skins;
    for(QHash<QString, QString>::const_iterator iter = m_themes.begin();
        iter != m_themes.end(); ++iter)
    {
        skins << *iter;
    }

    return skins;
}
#include <QStringList>
#include "qssmodule.h"
#include "qssloader.h"
#include <QDir>
#include <QPair>
#include <QDebug>

QssModule &QssModule::instance()
{
    static QssModule m_module("Qss");
    return m_module;
}

bool QssModule::load(const QVariant &val)
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
    QStringList qss = m_loader->findAllQss("./resource/qss");
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

        int dot = fileName.lastIndexOf('.');
        shortCut = fileName.left(dot);

        m_skins[shortCut] = name;
    }


    //load qss file named 'default' or the first qss file
    if(m_skins.contains(tr("default")))
        ret = m_loader->loadQss(m_skins[tr("default")]);
    else
        ret = m_loader->loadQss(m_skins.begin().value());

    if(ret)
        m_isLoaded = true;

    return ret;
}

void QssModule::unload()
{
    if(m_loader)
    {
        m_skins.clear();
        delete m_loader;
    }

    m_isLoaded = false;
    m_error = tr("No error");
}

bool QssModule::canRunInThread() const
{
    return false;
}

QStringList QssModule::skins()
{
    QStringList skins;
    for(QHash<QString, QString>::const_iterator iter = m_skins.begin();
        iter != m_skins.end(); ++iter)
    {
        skins << *iter;
    }

    return skins;
}

QssModule::QssModule(const QString &name) :
    BaseAppModule(name),
    m_loader(NULL)
{
    m_skins.clear();
}

QssModule::~QssModule()
{
    unload();
    emit deleted();
}

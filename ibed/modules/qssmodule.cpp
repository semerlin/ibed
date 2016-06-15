#include <QStringList>
#include "qssmodule.h"
#include "qssloader.h"
#include <QDir>

QssModule &QssModule::instance()
{
    static QssModule m_module("Qss");
    return m_module;
}

bool QssModule::load(const QVariant &val)
{
    if(m_loader == NULL)
    {
        m_loader = new QssLoader;
        if(m_loader != NULL)
        {
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
                    fileName = name.mid(splash);
                }

                int dot = fileName.lastIndexOf('.');
                shortCut = fileName.left(dot + 1);

                m_skins[shortCut] = name;
            }

            //load qss file named 'default' or the first qss file
            if(m_skins.contains(tr("default")))
                return m_loader->loadQss(m_skins[tr("default")]);
            else
                return m_loader->loadQss(m_skins.begin().value());
        }
        else
        {
            m_error = QObject::tr("No enough memory space!");
            return false;
        }
    }
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

QssModule::QssModule(const QString &name) :
    BaseAppModule(name),
    m_loader(NULL)
{
    m_skins.clear();
}

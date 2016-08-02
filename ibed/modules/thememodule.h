#ifndef THEMEMODULE_H
#define THEMEMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"
#include <QHash>

class QssLoader;

class MODULESSHARED_EXPORT ThemeModule : public BaseAppModule
{
public:
    ThemeModule(const QString &name);
    ~ThemeModule();

public:
    bool load(const QVariant &val);
    void unload();
    QStringList themes(void);

private:
    QssLoader *m_loader;
    QHash<QString, QString> m_themes;  //shortcut name first
};

#endif // QSSMODULE_H

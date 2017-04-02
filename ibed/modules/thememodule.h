#ifndef THEMEMODULE_H
#define THEMEMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class ThemeModulePrivate;

class MODULESSHARED_EXPORT ThemeModule : public BaseAppModule
{
public:
    ThemeModule(const QString &name);
    ~ThemeModule();

public:
    bool load(const QVariant &val);
    void unload();
    QStringList themes(void);
    void changeToTheme(const QString &theme);

private:
    ThemeModulePrivate * const d_ptr;
    Q_DECLARE_PRIVATE(ThemeModule);
    Q_DISABLE_COPY(ThemeModule);
};

#endif // QSSMODULE_H

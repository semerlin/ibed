#ifndef THEMEMODULE_H
#define THEMEMODULE_H

#include "modules_global.h"
#include "baseappmodule.h"

class ThemeModulePrivate;

/**
 * @brief application theme control class
 */
class MODULESSHARED_EXPORT ThemeModule : public BaseAppModule
{
    Q_OBJECT
public:
    ThemeModule(const QString &name);
    ~ThemeModule();

public:
    bool load(const QVariant &val);
    void unload();
    /**
     * @brief get all supportted themes
     * @return all themes
     */
    QStringList themes(void);

    /**
     * @brief change application theme
     * @param theme - theme name
     */
    void changeToTheme(const QString &theme);

signals:
    /**
     * @brief signals is emitted if theme change success
     * @param name - current theme name
     */
    void themeChanged(const QString &name);

private:
    ThemeModulePrivate * const d_ptr;
    Q_DECLARE_PRIVATE(ThemeModule);
    Q_DISABLE_COPY(ThemeModule);
};

#endif // QSSMODULE_H

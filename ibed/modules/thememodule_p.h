#ifndef THEMEMODULE_P_H
#define THEMEMODULE_P_H

#include "modules_global.h"
#include <QHash>

class MODULESSHARED_EXPORT ThemeModulePrivate
{
public:
    QHash<QString, QString> m_themes;  //shortcut name first
};

#endif // THEMEMODULE_P


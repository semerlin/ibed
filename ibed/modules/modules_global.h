#ifndef MODULES_GLOBAL_H
#define MODULES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODULES_LIBRARY)
#  define MODULESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MODULESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MODULES_GLOBAL_H

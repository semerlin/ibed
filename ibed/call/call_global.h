#ifndef CALL_GLOBAL_H
#define CALL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CALL_LIBRARY)
#  define CALLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CALLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CALL_GLOBAL_H

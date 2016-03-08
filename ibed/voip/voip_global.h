#ifndef VOIP_GLOBAL_H
#define VOIP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VOIP_LIBRARY)
#  define VOIPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define VOIPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // VOIP_GLOBAL_H

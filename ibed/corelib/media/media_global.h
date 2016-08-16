#ifndef MEDIA_GLOBAL_H
#define MEDIA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MEDIA_LIBRARY)
#  define MEDIASHARED_EXPORT Q_DECL_EXPORT
#else
#  define MEDIASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MEDIA_GLOBAL_H

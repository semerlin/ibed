#ifndef INPUTMETHOD_GLOBAL_H
#define INPUTMETHOD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INPUTMETHOD_LIBRARY)
#  define INPUTMETHODSHARED_EXPORT Q_DECL_EXPORT
#else
#  define INPUTMETHODSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // INPUTMETHOD_GLOBAL_H

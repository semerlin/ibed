#ifndef PATIENT_GLOBAL_H
#define PATIENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PATIENT_LIBRARY)
#  define PATIENTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PATIENTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PATIENT_GLOBAL_H

#ifndef HELPER_CLASS_GLOBAL_H
#define HELPER_CLASS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HELPER_CLASS_LIBRARY)
#  define HELPER_CLASS_EXPORT Q_DECL_EXPORT
#else
#  define HELPER_CLASS_EXPORT Q_DECL_IMPORT
#endif

#endif // HELPER_CLASS_GLOBAL_H
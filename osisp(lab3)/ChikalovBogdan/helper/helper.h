#ifndef HELPER_H
#define HELPER_H

#include "helper_global.h"

#include <QMap>
#include <QLabel>

extern "C" HELPER_EXPORT void SetFalse(QMap<QString, bool> &);
extern "C" HELPER_EXPORT void SetLabS(QLabel &);
extern "C" HELPER_EXPORT void SetLabN(QLabel &);

#endif // HELPER_H
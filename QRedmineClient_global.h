#pragma once

#include <QtCore/qglobal.h>

#if defined(QREDMINECLIENT_LIBRARY)
#  define QREDMINECLIENT_EXPORT Q_DECL_EXPORT
#else
#  define QREDMINECLIENT_EXPORT Q_DECL_IMPORT
#endif

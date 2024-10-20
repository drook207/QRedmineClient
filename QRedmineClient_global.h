#pragma once

#include <QString>
#include <QtCore/qglobal.h>

#if defined(QREDMINECLIENT_LIBRARY)
#define QREDMINECLIENT_EXPORT Q_DECL_EXPORT
#else
#define QREDMINECLIENT_EXPORT Q_DECL_IMPORT
#endif

namespace QRedmine {
// https://stackoverflow.com/questions/56201976/qt-vs-constexpr-string-literal
struct ConstLatin1String : public QLatin1String {
  constexpr ConstLatin1String(const char *const s)
	  : QLatin1String(s, static_cast<int>(std::char_traits<char>::length(s))) {}
};

constexpr ConstLatin1String CONTENT_TYPE_JSON =
	"Content-Type: application/json";
constexpr ConstLatin1String CONTENT_TYPE_XML = "Content-Type: application/xml";
constexpr ConstLatin1String AUTHORIZATION = "Authorization";
constexpr ConstLatin1String BASIC_HTTP = "Basic";
constexpr ConstLatin1String X_REDMNE_APP_KEY = "X-Redmine-API-Key";
} // namespace QRedmine

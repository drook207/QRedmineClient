#include "tokenauthentication.h"
#include "qredmineclient_global.h"
#include <QLoggingCategory>

namespace QRedmine {

Q_LOGGING_CATEGORY(lcTokenAuthenticator, "qredmineclient.tokenauthenticator")

TokenAuthentication::TokenAuthentication(const QStringView& apiKey, QObject* parent)
	: Authentication(parent)
	, mApiKey(apiKey.toLatin1())
{
}

void TokenAuthentication::addAuthenticationToRequest(QNetworkRequest& request)
{
	request.setRawHeader(X_REDMNE_APP_KEY.latin1(), mApiKey);
}

} // namespace QRedmine

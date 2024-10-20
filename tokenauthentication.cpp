#include "tokenauthentication.h"
#include "QRedmineClient_global.h"
#include <QLoggingCategory>

namespace QRedmine {

Q_LOGGING_CATEGORY(lcTokenAuthenticator, "qredmineclient.tokenauthenticator")
TokenAuthentication::TokenAuthentication(const QStringView &apiKey,
										 QObject *parent)
	: Authenticator(parent), mApiKey(apiKey.toLatin1()) {}

void TokenAuthentication::addAuthenticationToRequest(
	QNetworkRequest *const request) {
  if (nullptr == request) {
	qWarning(lcTokenAuthenticator) << "Invalid request!";
	return;
  }
  request->setRawHeader(X_REDMNE_APP_KEY.latin1(), mApiKey);
}

} // namespace QRedmine

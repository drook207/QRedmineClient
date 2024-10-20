#include "passwordauthentication.h"
#include "qredmineclient_global.h"
#include <QLoggingCategory>
namespace QRedmine {
Q_LOGGING_CATEGORY(lcPasswordAuthenticator,
				   "qredmineclient.passwordauthenticator")
PasswordAuthentication::PasswordAuthentication(const QStringView &username,
											   const QStringView &password,
											   QObject *parent)
	: Authentication(parent), mUsername(username.toLatin1()),
	  mPassword(password.toLatin1().toBase64()) {}

void PasswordAuthentication::addAuthenticationToRequest(
	QNetworkRequest *const request) {
  if (nullptr == request) {
	qWarning(lcPasswordAuthenticator) << "Invalid request!";
	return;
  }

  const auto data =
	  QByteArray(BASIC_HTTP.latin1() + mUsername + ":" + mPassword);
  qDebug(lcPasswordAuthenticator) << "Authentication date=" << data;
  request->setRawHeader(AUTHORIZATION.latin1(), data);
}

} // namespace QRedmine

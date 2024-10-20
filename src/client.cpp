#include "client.h"
#include "passwordauthentication.h"
#include "tokenauthentication.h"
#include <QLoggingCategory>
#include <QNetworkReply>

namespace QRedmine {

Q_LOGGING_CATEGORY(lcClient, "qredmineclient.client")
Client::Client(QObject *parent) : QObject(parent) {}

Client::Client(const QUrl url, QObject *parent) : QObject(parent), mUrl(url) {}

Client::Client(const QUrl &url, const QStringView &apiKey, bool sslVerify,
			   QObject *parent)
	: QObject(parent), mSslVerify(sslVerify), mUrl(url) {

  if (!setAuthenticationMethod(apiKey)) {
	qDebug(lcClient) << "Failed to set authentication method. For further "
						"information check logg";
  }
}

Client::Client(const QUrl &url, const QStringView &username,
			   const QStringView &password, bool sslVerify, QObject *parent)
	: QObject(parent), mSslVerify(sslVerify), mUrl(url) {
  if (!setAuthenticationMethod(username, password)) {
	qDebug(lcClient) << "Failed to set authentication method. For further "
						"information check logg";
  }
}

bool Client::setAuthenticationMethod(const QStringView &apiKey) {
  if (nullptr != mAuthenticator) {
	qWarning(lcClient)
		<< "Authentication method could not be changed within a session!";
	return false;
  }
  if (apiKey.isEmpty()) {
	qWarning(lcClient)
		<< "No api key provieded, please reset the authentication method with "
		   "setAuthenticationMethod().";
	return false;
  }
  mAuthenticator = new TokenAuthentication(apiKey, this);
  return true;
}

bool Client::setAuthenticationMethod(const QStringView &username,
									 const QStringView &password) {
  if (nullptr != mAuthenticator) {
	qWarning(lcClient)
		<< "Authentication method could not be changed within a session!";
	return false;
  }
  if (username.isEmpty() || password.isEmpty()) {
	qWarning(lcClient) << "No username or password provieded, please reset the "
						  "authentication method with "
						  "setAuthenticationMethod().";
	return false;
  }
  mAuthenticator = new PasswordAuthentication(username, password, this);
  return true;
}

void Client::reconnect() {

  if (nullptr != mManger) {
	mManger->deleteLater();
  }

  mManger = new QNetworkAccessManager(this);

  connect(mManger, &QNetworkAccessManager::finished, this,
		  &Client::replyFinished);
  connect(mManger, &QNetworkAccessManager::sslErrors, this,
		  &Client::handleSslError);
}

QUrl Client::Url() const { return mUrl; }

void Client::setUrl(const QUrl &newUrl) { mUrl = newUrl; }

bool Client::SslVerify() const { return mSslVerify; }

void Client::setSslVerify(bool newSslVerify) { mSslVerify = newSslVerify; }

QString Client::UserAgent() const { return mUserAgent; }

void Client::setUserAgent(const QString &newUserAgent) {
  mUserAgent = newUserAgent;
}

void Client::handleSslError(QNetworkReply *const reply,
							const QList<QSslError> &errors) {
  if (!mSslVerify) {
	reply->ignoreSslErrors();
  }
}

void Client::replyFinished(QNetworkReply *const reply) {}

void Client::init() {
  if (mUrl.isEmpty() || !mUrl.isValid()) {
	qDebug(lcClient) << "No valid url is set.";
	return;
  }
  reconnect();

  emit initialised();
}

} // namespace QRedmine

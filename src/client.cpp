#include "client.h"
#include "passwordauthentication.h"
#include "tokenauthentication.h"
#include <QLoggingCategory>
#include <QNetworkReply>

namespace QRedmine {

Q_LOGGING_CATEGORY(lcClient, "qredmineclient.client")

Client::Client(QObject* parent)
	: QObject(parent)
{
}

Client::Client(const QUrl url, QObject* parent)
	: QObject(parent)
	, mUrl(url)
{
}

Client::Client(const QUrl& url, const QStringView& apiKey, bool sslVerify, QObject* parent)
	: QObject(parent)
	, mSslVerify(sslVerify)
	, mUrl(url)
{
	if (!setAuthenticationMethod(apiKey)) {
		qDebug(lcClient) << "Failed to set authentication method. For further "
							"information check logg";
	}
}

Client::Client(
	const QUrl& url, const QStringView& username, const QStringView& password, bool sslVerify, QObject* parent)
	: QObject(parent)
	, mSslVerify(sslVerify)
	, mUrl(url)
{
	if (!setAuthenticationMethod(username, password)) {
		qDebug(lcClient) << "Failed to set authentication method. For further "
							"information check logg";
	}
}

bool Client::setAuthenticationMethod(const QStringView& apiKey)
{
	if (nullptr != mAuthenticator) {
		qWarning(lcClient) << "Authentication method could not be changed within a session!";
		return false;
	}
	if (apiKey.isEmpty()) {
		qWarning(lcClient) << "No api key provided, please reset the authentication method with "
							  "setAuthenticationMethod().";
		return false;
	}
	mAuthenticator = new TokenAuthentication(apiKey, this);
	return true;
}

bool Client::setAuthenticationMethod(const QStringView& username, const QStringView& password)
{
	if (nullptr != mAuthenticator) {
		qWarning(lcClient) << "Authentication method could not be changed within a session!";
		return false;
	}
	if (username.isEmpty() || password.isEmpty()) {
		qWarning(lcClient) << "No username or password provided, please reset the "
							  "authentication method with "
							  "setAuthenticationMethod().";
		return false;
	}
	mAuthenticator = new PasswordAuthentication(username, password, this);
	return true;
}

void Client::reconnect()
{
	if (nullptr != mManager) {
		mManager->deleteLater();
	}

	mManager = new QNetworkAccessManager(this);

	connect(mManager, &QNetworkAccessManager::finished, this, &Client::replyFinished);
	connect(mManager, &QNetworkAccessManager::sslErrors, this, &Client::handleSslError);
}

QUrl Client::Url() const { return mUrl; }

void Client::setUrl(const QUrl& newUrl) { mUrl = newUrl; }

bool Client::SslVerify() const { return mSslVerify; }

void Client::setSslVerify(bool newSslVerify) { mSslVerify = newSslVerify; }

QString Client::UserAgent() const { return mUserAgent; }

void Client::setUserAgent(const QString& newUserAgent) { mUserAgent = newUserAgent; }

void Client::handleSslError(QNetworkReply* const reply, const QList<QSslError>& errors)
{
	if (!mSslVerify) {
		reply->ignoreSslErrors();
	}
}

void Client::replyFinished(QNetworkReply* const reply) { }

void Client::init()
{
	if (mUrl.isEmpty() || !mUrl.isValid()) {
		qDebug(lcClient) << "No valid url is set.";
		return;
	}
	reconnect();

	emit initialized();
}

bool Client::sendRequest(int id, Request* const request)
{
	if (nullptr == mManager) {
		qDebug(lcClient) << "Client is not initialized";
		return false;
	}

	if (nullptr == request) {
		qDebug(lcClient) << "No request provided";
		return false;
	}

	if (request->Resource().isEmpty()) {
		qDebug(lcClient) << "No resource provided";
		return false;
	}

	if (request->Parameters().isEmpty()) {
		qDebug(lcClient) << "No parameters provided";
		return false;
	}

	const QUrl restRequest = mUrl.toString() + "/" + request->Resource() + ".json" + request->Parameters();

	if (!restRequest.isValid()) {
		qDebug(lcClient) << "Invalid Url.";
		return false;
	}

	auto networkRequest = request->NetworkRequest();
	networkRequest.setUrl(restRequest);
	networkRequest.setRawHeader("User-Agent", mUserAgent.toLatin1());
	networkRequest.setRawHeader("X-Custom-User-Agent", mUserAgent.toLatin1());
	mAuthenticator->addAuthenticationToRequest(networkRequest);

	QNetworkReply* reply {};
	switch (request->Mode()) {
		case QNetworkAccessManager::HeadOperation:
			break;
		case QNetworkAccessManager::GetOperation:
			reply = mManager->get(networkRequest);
			break;
		case QNetworkAccessManager::PutOperation:
			reply = mManager->put(networkRequest, request->PostData());
			break;
		case QNetworkAccessManager::PostOperation:
			reply = mManager->post(networkRequest, request->PostData());
			break;
		case QNetworkAccessManager::DeleteOperation:
			reply = mManager->deleteResource(networkRequest);
			break;
		case QNetworkAccessManager::CustomOperation:
			break;
		case QNetworkAccessManager::UnknownOperation:
			break;
	}
	if (nullptr == reply) {
		qDebug(lcClient) << "Invalid network reply.";
		return false;
	}
	request->setReply(reply);
	connect(reply, &QNetworkReply::finished, request, &Request::requestFinished);
	connect(reply, &QNetworkReply::errorOccurred, request, &Request::errorOccured);
	connect(request, &Request::finished, reply, &QNetworkReply::deleteLater);

	return true;
}

} // namespace QRedmine

#pragma once

#include "authentication.h"
#include "qredmineclient_global.h"
#include "request.h"
#include "timeentryjson.h"
#include <QNetworkAccessManager>
#include <QObject>

namespace QRedmine {
class QREDMINECLIENT_EXPORT Client : public QObject {
	Q_OBJECT
public:
	Client(QObject* parent = nullptr);

	Client(const QUrl url, QObject* parent = nullptr);

	Client(const QUrl& url, const QStringView& apiKey, bool sslVerify = true, QObject* parent = nullptr);

	Client(const QUrl& url, const QStringView& username, const QStringView& password, bool sslVerify = true,
		QObject* parent = nullptr);

	[[nodiscard]] bool setAuthenticationMethod(const QStringView& apiKey);
	[[nodiscard]] bool setAuthenticationMethod(const QStringView& username, const QStringView& password);

	void reconnect();

	[[nodiscard]] QUrl Url() const;
	void setUrl(const QUrl& newUrl);

	[[nodiscard]] bool SslVerify() const;
	void setSslVerify(bool newSslVerify);

	[[nodiscard]] QString UserAgent() const;
	void setUserAgent(const QString& newUserAgent);

	bool timeEntry(TimeEntryRequest& request, const qint32 id);

public slots:

	void handleSslError(QNetworkReply* const reply, const QList<QSslError>& errors);

	void replyFinished(QNetworkReply* const reply);
signals:
	void initialized();

private:
	void init();
	bool sendRequest(int id, Request* const request);
	QNetworkAccessManager* mManager {};

	QUrl mUrl {};
	bool mSslVerify = true;
	Authentication* mAuthenticator {};
	QString mUserAgent {};
};
} // namespace QRedmine

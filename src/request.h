#pragma once

#include "qredmineclient_global.h"
#include <QNetworkRequest>
#include <QObject>
#include <qnetworkreply.h>

namespace QRedmine {

class Request : public QObject {
	Q_OBJECT
public:
	explicit Request(QObject* parent = nullptr);

	[[nodiscard]] QString Resource() const;

	void setReply(QNetworkReply* newReply);

	void setParameters(const QString& newParameters);

	[[nodiscard]] QString Parameters() const;

	[[nodiscard]] QNetworkRequest NetworkRequest() const;

	[[nodiscard]] QNetworkAccessManager::Operation Mode() const;
	[[nodiscard]] QByteArray PostData() const;

public slots:
	virtual void requestFinished();
	void errorOccured(QNetworkReply::NetworkError networkError);

protected:
	QNetworkRequest mRequest {};
	QNetworkReply* mReply {};
	qint32 mId = DEFAULT_ID;
	QString mResource {};
	QString mParameters {};
	QNetworkAccessManager::Operation mMode {};
	QByteArray mPostData {};
	void resourceRequestMode();

signals:
	void finished();
	void error();
	void timeout();
};

} // namespace QRedmine

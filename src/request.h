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

protected:
	QNetworkRequest mRequest {};
	QNetworkReply* mReply {};
	qint32 mId = DEFAULT_ID;

signals:
	void finished();
	void timeout();

private slots:
	virtual void requestFinished();
};

} // namespace QRedmine

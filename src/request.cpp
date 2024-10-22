#include "request.h"
#include "QLoggingCategory"

namespace QRedmine {

Q_LOGGING_CATEGORY(lcRequest, "qredmineclient.request")

Request::Request(QObject* parent)
	: QObject(parent)
{
}

QString Request::Resource() const { return mResource; }

void Request::setReply(QNetworkReply* newReply) { mReply = newReply; }

void Request::setParameters(const QString& newParameters) { mParameters = newParameters; }

QString Request::Parameters() const { return mParameters; }

QNetworkRequest Request::NetworkRequest() const { return mRequest; }

QNetworkAccessManager::Operation Request::Mode() const { return mMode; }

QByteArray Request::PostData() const { return mPostData; }

void Request::errorOccured(QNetworkReply::NetworkError networkError)
{
	qWarning(lcRequest) << "Networkerror occurred: " << networkError;
	emit error();
}

void Request::resourceRequestMode()
{
	if (mId == DEFAULT_ID) {
		mMode = QNetworkAccessManager::PostOperation;
		return;
	}
	mMode = QNetworkAccessManager::PutOperation;
	mResource.append("/" + QString::number(mId));
}

} // namespace QRedmine

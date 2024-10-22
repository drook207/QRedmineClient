#include "jsonrequest.h"

namespace QRedmine {

JsonRequest::JsonRequest(QObject* parent)
	: Request(parent)
{
	mRequest.setRawHeader("Content-Type", "application/json");
}

QJsonDocument JsonRequest::Data() const { return mData; }

void JsonRequest::setData(const QJsonDocument& newData) { mData = newData; }

} // namespace QRedmine

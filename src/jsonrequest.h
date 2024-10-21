#pragma once

#include "QJsonObject"
#include "request.h"

namespace QRedmine {

class JsonRequest : public Request {
public:
	JsonRequest(QObject* parent = nullptr);
	virtual void toJson() = 0;
	virtual void fromJson() = 0;

private:
	QJsonObject mData {};
};

} // namespace QRedmine

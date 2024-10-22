#pragma once

#include "request.h"
#include <QJsonDocument>

namespace QRedmine {

class JsonRequest : public Request {
public:
	JsonRequest(QObject* parent = nullptr);
	virtual bool toJson() = 0;
	virtual bool fromJson() = 0;

	[[nodiscard]] QJsonDocument Data() const;
	void setData(const QJsonDocument& newData);

protected:
	QJsonDocument mData {};
};

} // namespace QRedmine

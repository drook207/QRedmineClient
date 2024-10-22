#pragma once

#include "jsonrequest.h"
#include "timeentry.h"

namespace QRedmine {

class TimeEntryRequest : public JsonRequest {
public:
	TimeEntryRequest(TimeEntry entry = TimeEntry(), QObject* parent = nullptr);

private:
	TimeEntry mEntry {};
	// Request interface
private slots:
	void requestFinished() override;

	// JsonRequest interface
public:
	bool toJson() override;
	[[nodiscard]] bool fromJson() override;
};

} // namespace QRedmine

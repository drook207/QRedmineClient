#pragma once

#include "jsonrequest.h"
#include "timeentry.h"

namespace QRedmine {

class TimeEntryJson : public JsonRequest {
public:
	TimeEntryJson(TimeEntry entry = TimeEntry(), QObject* parent = nullptr);

private:
	TimeEntry mEntry {};
	// Request interface
private slots:
	void requestFinished() override;

	// JsonRequest interface
public:
	void toJson() override;
	void fromJson() override;
};

} // namespace QRedmine

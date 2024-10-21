#include "timeentryjson.h"
#include <QLoggingCategory>

namespace QRedmine {
Q_LOGGING_CATEGORY(lcTimeEntryJson, "qredmine.timeentryjson")

TimeEntryJson::TimeEntryJson(TimeEntry entry, QObject* parent)
	: JsonRequest(parent)
{
}

void TimeEntryJson::toJson()
{
	if (mEntry.hours < 0.01f) {
		qDebug(lcTimeEntryJson) << "Time entry has to be at least 36 seconds";
		return;
	}
}

} // namespace QRedmine

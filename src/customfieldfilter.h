#pragma once

#include "qredmineclient_global.h"
#include <QString>

namespace QRedmine {

struct CustomFieldFilter {
	int projectId = DEFAULT_ID;
	int trackerId = DEFAULT_ID;
	QString type;
	QString format;
};

} // namespace QRedmine

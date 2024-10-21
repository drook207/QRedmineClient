#pragma once

#include "resource.h"

namespace QRedmine {

struct IssueStatus : Resource {
	int id = DEFAULT_ID;
	QString name;
	bool isClosed;
	bool isDefault;
};

} // namespace QRedmine

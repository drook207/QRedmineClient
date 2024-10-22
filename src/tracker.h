#pragma once

#include "resource.h"

namespace QRedmine {

struct Tracker : Resource {
	int id = DEFAULT_ID;
	QString name;
};

} // namespace QRedmine

#pragma once

#include "resource.h"

namespace QRedmine {

struct Project : Resource {
	int id = DEFAULT_ID;

	QString description;
	QString identifier;
	bool isPublic;
	QString name;
	Item parent;

	Items trackers;
	Items categories;
};

} // namespace QRedmine

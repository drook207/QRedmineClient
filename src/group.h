#pragma once

#include "resource.h"

namespace QRedmine {

struct Group : Resource {
	int id = DEFAULT_ID;
	QString name;
	Items members;
};

} // namespace QRedmine

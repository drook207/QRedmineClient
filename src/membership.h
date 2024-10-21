#pragma once

#include "resource.h"

namespace QRedmine {

struct Membership : Resource {
	int id = DEFAULT_ID;
	Item project;
	Item user;
	Item group;
	Items roles;
};

} // namespace QRedmine

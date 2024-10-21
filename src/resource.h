#pragma once

#include "item.h"
#include <QDateTime>

namespace QRedmine {
struct Resource {
	QDateTime createdOn;
	QDateTime updatedOn;
	Item user;
};

} // namespace QRedmine

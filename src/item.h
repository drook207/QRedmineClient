#pragma once

#include "qredmineclient_global.h"
#include <QString>

namespace QRedmine {

struct Item {
	int id = DEFAULT_ID;
	QString name;
};

using Items = QList<Item>;
} // namespace QRedmine

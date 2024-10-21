#pragma once

#include <QString>

namespace QRedmine {

struct RedmineOptions {
	RedmineOptions(QString parameters = QLatin1String(), bool getAllItems = false)
		: parameters(parameters)
		, getAllItems(getAllItems)
	{
	}

	QString parameters;
	bool getAllItems = false;
};

} // namespace QRedmine

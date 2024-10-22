#pragma once

#include "item.h"
#include "qredmineclient_global.h"
#include <QString>

namespace QRedmine {

struct CustomField {
	int id = DEFAULT_ID;
	QString name;

	QList<QString> values;
	QList<QString> possibleValues;
	QString defaultValue;

	QString type;
	QString format;
	QString regex;
	int minLength;
	int maxLength;

	bool allProjects;
	bool isRequired;
	bool isFilter;
	bool searchable;
	bool multiple;
	bool visible;

	Items projects;
	Items trackers;
};

using CustomFields = QList<CustomField>;

} // namespace QRedmine

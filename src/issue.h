#pragma once

#include "customfield.h"
#include "resource.h"

namespace QRedmine {

struct Issue : Resource {
	int id = DEFAULT_ID;
	int parentId = DEFAULT_ID;

	QString description;
	double doneRatio = 0;
	QString subject;

	Item assignedTo;
	Item author;
	Item category;
	Item priority;
	Item project;
	Item status;
	Item tracker;
	Item version;

	QDate dueDate;
	double estimatedHours = 0;
	QDate startDate;

	CustomFields customFields;
};

} // namespace QRedmine

#include "timeentryjson.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QLoggingCategory>

namespace QRedmine {
Q_LOGGING_CATEGORY(lcTimeEntryJson, "qredmine.timeentryjson")

TimeEntryRequest::TimeEntryRequest(TimeEntry entry, QObject* parent)
	: JsonRequest(parent)

{
	mResource = QStringLiteral("time_entries");

	if (TimeEntryRequest::toJson()) {
		mRequest.setRawHeader("Content-Length", QByteArray::number(mData.toJson().size()));
		resourceRequestMode();
		mPostData = mData.toJson();
		return;
	}
	mMode = QNetworkAccessManager::GetOperation;
}

void TimeEntryRequest::requestFinished()
{
	QByteArray rawData = mReply->readAll();
	mData = QJsonDocument::fromJson(rawData);
	if (fromJson()) {
		return emit finished();
	}
	return emit error();
}

bool TimeEntryRequest::toJson()
{
	if (mEntry.hours < 0.01f) {
		qDebug(lcTimeEntryJson) << "Time entry has to be at least 36 seconds";
		return false;
	}

	if (mEntry.issue.id == DEFAULT_ID && mEntry.project.id == DEFAULT_ID) {
		qDebug(lcTimeEntryJson) << "Either issue id or project id must be specified.";
		return false;
	}

	QJsonObject attributes;

	attributes["hours"] = mEntry.hours;

	if (mEntry.activity.id != DEFAULT_ID) {
		attributes["activity_id"] = mEntry.activity.id;
	}

	if (!mEntry.comment.isEmpty()) {
		attributes["comments"] = mEntry.comment;
	}

	if (mEntry.issue.id != DEFAULT_ID) {
		attributes["issue_id"] = mEntry.issue.id;
	}

	if (mEntry.project.id != DEFAULT_ID) {
		attributes["project_id"] = mEntry.project.id;
	}

	if (mEntry.spentOn.isValid()) {
		attributes["spent_on"] = mEntry.spentOn.toString(Qt::ISODate);
	}

	if (!mEntry.customFields.isEmpty()) {
		QJsonArray customFields;

		for (const auto& field : std::as_const(mEntry.customFields)) {
			QJsonObject customField;
			customField["id"] = field.id;
			customField["value"] = field.values.at(0);
			customFields.append(customField);
		}

		attributes["custom_fields"] = customFields;
	}

	QJsonObject data;
	data["time_entry"] = attributes;

	mData.setObject(data);

	return true;
}

bool TimeEntryRequest::fromJson()
{
	if (mData.isEmpty() || mData.isNull()) {
		qDebug(lcTimeEntryJson) << "Time entry has to be at least 36 seconds";
		return false;
	}
	mEntry.hours = mData["hours"].toDouble();

	mEntry.activity.id = mData["activity_id"].toInt();

	mEntry.comment = mData["comments"].toString();

	mEntry.issue.id = mData["issue_id"].toInt();

	mEntry.project.id = mData["project_id"].toInt();

	mEntry.spentOn = mData["spent_on"].toVariant().toDate();

	return true;
}

} // namespace QRedmine

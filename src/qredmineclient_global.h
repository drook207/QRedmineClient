#pragma once

#include <QString>
#include <QtCore/qglobal.h>
#include <qdatetime.h>

#if defined(QREDMINECLIENT_LIBRARY)
#define QREDMINECLIENT_EXPORT Q_DECL_EXPORT
#else
#define QREDMINECLIENT_EXPORT Q_DECL_IMPORT
#endif

namespace QRedmine {
// https://stackoverflow.com/questions/56201976/qt-vs-constexpr-string-literal
struct ConstLatin1String : public QLatin1String {
  constexpr ConstLatin1String(const char *const s)
	  : QLatin1String(s, static_cast<int>(std::char_traits<char>::length(s))) {}
};

constexpr ConstLatin1String CONTENT_TYPE_JSON =
	"Content-Type: application/json";
constexpr ConstLatin1String CONTENT_TYPE_XML = "Content-Type: application/xml";
constexpr ConstLatin1String AUTHORIZATION = "Authorization";
constexpr ConstLatin1String BASIC_HTTP = "Basic";
constexpr ConstLatin1String X_REDMNE_APP_KEY = "X-Redmine-API-Key";
constexpr auto NULL_ID = -1;

/// Redmine error codes
enum class RedmineError {
  NO_ERR,
  ERR_INCOMPLETE_DATA,
  ERR_NETWORK,
  ERR_NOT_SAVED,
  ERR_TIME_ENTRY_TOO_SHORT,
  ERR_TIMEOUT,
};

/// Redmine options
struct RedmineOptions {
  QString parameters;
  bool getAllItems = false;

  RedmineOptions(QString parameters = "", bool getAllItems = false)
	  : parameters(parameters), getAllItems(getAllItems) {}
};

/// Custom field filter
struct CustomFieldFilter {
  int projectId = NULL_ID; ///< Project
  int trackerId = NULL_ID; ///< Tracker
  QString type;            ///< Customised type
  QString format;          ///< Format
};

/// @name Redmine data structures
/// @{

/// Structure representing a Redmine item
struct Item {
  int id = NULL_ID; ///< ID
  QString name;     ///< Name
};

/// @}

/// @name Redmine data containers
/// @{

/// Redmine resource
struct RedmineResource {
  QDateTime createdOn; ///< Created on
  QDateTime updatedOn; ///< Updated on
  Item user;           ///< Redmine user
};

/// Item vector
using Items = QVector<Item>;

/// Structure representing an enumeration
struct Enumeration : RedmineResource {
  int id = NULL_ID; ///< ID
  QString name;     ///< Project name
  bool isDefault;   ///< Default entry
};

/// @}

/// @name Redmine data structures
/// @{

/// Structure representing a custom field
struct CustomField // no RedmineResource
{
  int id = NULL_ID; ///< ID
  QString name;     ///< Name

  QVector<QString> values;         ///< Value(s)
  QVector<QString> possibleValues; ///< Possible
  QString defaultValue;            ///< Default value

  QString type;   ///< Customised type
  QString format; ///< Field format
  QString regex;  ///< Regular expression
  int minLength;  ///< Minimum length
  int maxLength;  ///< Maximum length

  bool allProjects; ///< Custom field may be used by all projects
  bool isRequired;  ///< Custom field is required
  bool isFilter;    ///< Custom field may be used as filter
  bool searchable;  ///< Custom field is searchable
  bool multiple;    ///< Custom field may contain multiple values
  bool visible;     ///< Custom field is visible

  Items projects; ///< Custom field is allowed in these projects
  Items trackers; ///< Custom field is allowed in these trackers
};

/// @}

/// @name Redmine data containers
/// @{

/// Custom field vector
using CustomFields = QVector<CustomField>;

/// @}

/// @name Redmine data structures
/// @{

/// Structure representing a group
struct Group : RedmineResource {
  int id = NULL_ID; ///< ID
  QString name;     ///< Group name
  Items members;    ///< Group members
};

/// Structure representing an issue
struct Issue : RedmineResource {
  int id = NULL_ID;       ///< ID
  int parentId = NULL_ID; ///< Parent issue ID

  QString description;  ///< Description
  double doneRatio = 0; ///< Done ratio
  QString subject;      ///< Subject

  Item assignedTo; ///< Assigned to user
  Item author;     ///< Author
  Item category;   ///< Category
  Item priority;   ///< Priority
  Item project;    ///< Project
  Item status;     ///< Status
  Item tracker;    ///< Tracker
  Item version;    ///< Version

  QDate dueDate;             ///< Due date
  double estimatedHours = 0; ///< Estimated hours
  QDate startDate;           ///< Start date

  CustomFields customFields; ///< Custom fields vector
};

/// Structure representing an issue category
struct IssueCategory // no RedmineResource
{
  int id = NULL_ID; ///< ID
  QString name;     ///< Issue category name
  Item project;     ///< Associated project
  Item assignedTo;  ///< Assigned to user
};

/// Structure representing an issue status
struct IssueStatus : RedmineResource {
  int id = NULL_ID; ///< ID
  QString name;     ///< Issue status name
  bool isClosed;    ///< Closed status
  bool isDefault;   ///< Default entry
};

/// Structure representing a membership
struct Membership : RedmineResource {
  int id = NULL_ID; ///< ID
  Item project;     ///< Project this membership is related to
  Item user;        ///< User within the project (exclusive with group)
  Item group;       ///< Group within the project (exclusive with user)
  Items roles;      ///< Roles of the user or group
};

/// Structure representing a project
struct Project : RedmineResource {
  int id = NULL_ID; ///< ID

  QString description; ///< Description
  QString identifier;  ///< Internal identifier
  bool isPublic;       ///< Public project
  QString name;        ///< Project name
  Item parent;         ///< Parent project

  Items trackers;   ///< Trackers
  Items categories; ///< Issue categories
};

/// Structure representing a time entry
struct TimeEntry : RedmineResource {
  Item activity;    ///< Activity
  QString comment;  ///< Additional comment
  double hours = 0; ///< Hours spent
  Item issue;       ///< Issue (required if no project was specified)
  Item project;     ///< Project (required if no issue was specified)
  QDate spentOn;    ///< Date of the time spent

  CustomFields customFields; ///< Custom fields vector
};

/// Structure representing a tracker
struct Tracker : RedmineResource {
  int id = NULL_ID; ///< ID
  QString name;     ///< Tracker name
};

/// Structure representing a user
struct User : RedmineResource {
  int id = NULL_ID; ///< ID

  QString login;     ///< Login name
  QString firstname; ///< First name
  QString lastname;  ///< Last name

  QString mail;          ///< E-mail address
  QDateTime lastLoginOn; ///< Last login time and date
};

enum class VersionStatus {
  OPEN,
  LOCKED,
  CLOSED,
};

enum class VersionSharing {
  NONE,
  DESCENDANTS,
  HIERARCHY,
  TREE,
  SYSTEM,
};
} // namespace QRedmine

#pragma once

#include <QObject>

namespace QRedmineClient {

	class PasswordAuthentication : public QObject
	{
		Q_OBJECT
	public:
		explicit PasswordAuthentication(QObject *parent = nullptr);

	signals:

	};

	} // namespace QRedmineClient


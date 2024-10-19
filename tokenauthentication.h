#pragma once

#include <QObject>

namespace QRedmineClient {

	class TokenAuthentication : public QObject
	{
		Q_OBJECT
	public:
		explicit TokenAuthentication(QObject *parent = nullptr);

	signals:

	};

	} // namespace QRedmineClient


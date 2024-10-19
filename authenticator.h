#pragma once

#include <QObject>

namespace QRedmineClient {

	class Authenticator : public QObject
	{
		Q_OBJECT
	public:
		explicit Authenticator(QObject *parent = nullptr);

	signals:

	};

	} // namespace QRedmineClient


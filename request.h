#pragma once

#include <QObject>

namespace QRedmine {

	class Request : public QObject
	{
		Q_OBJECT
	public:
		explicit Request(QObject *parent = nullptr);

	signals:

	};

	} // namespace QRedmineClient


#pragma once

#include "authentication.h"
#include <QObject>

namespace QRedmine {

class PasswordAuthentication : public Authentication {
	Q_OBJECT
public:
	explicit PasswordAuthentication(
		const QStringView& username, const QStringView& password, QObject* parent = nullptr);

private:
	QByteArray mUsername {};
	QByteArray mPassword {};

	// Authenticator interface
public:
	void addAuthenticationToRequest(QNetworkRequest& request) override;
};

} // namespace QRedmine

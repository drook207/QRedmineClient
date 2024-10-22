#pragma once

#include "authentication.h"
#include <QObject>

namespace QRedmine {

class TokenAuthentication : public Authentication {
	Q_OBJECT
public:
	explicit TokenAuthentication(const QStringView& apiKey, QObject* parent = nullptr);

private:
	QByteArray mApiKey {};

	// Authenticator interface
public:
	void addAuthenticationToRequest(QNetworkRequest& request) override;
};

} // namespace QRedmine

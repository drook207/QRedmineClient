#pragma once

#include "authenticator.h"
#include <QObject>

namespace QRedmine {

class TokenAuthentication : public Authenticator {
  Q_OBJECT
public:
  explicit TokenAuthentication(const QStringView &apiKey,
							   QObject *parent = nullptr);

private:
  QByteArray mApiKey{};

  // Authenticator interface
public:
  void addAuthenticationToRequest(const QNetworkRequest *request);
};

} // namespace QRedmine

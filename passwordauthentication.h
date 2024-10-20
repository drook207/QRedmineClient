#pragma once

#include "authenticator.h"
#include <QObject>

namespace QRedmine {

class PasswordAuthentication : public Authenticator {
  Q_OBJECT
public:
  explicit PasswordAuthentication(const QStringView &username,
								  const QStringView &password,
								  QObject *parent = nullptr);

private:
  QByteArray mUsername{};
  QByteArray mPassword{};

  // Authenticator interface
public:
  void addAuthenticationToRequest(QNetworkRequest* const request);
};

} // namespace QRedmine

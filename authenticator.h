#pragma once

#include <QNetworkRequest>
#include <QObject>

namespace QRedmine {

class Authenticator : public QObject {
  Q_OBJECT
public:
  explicit Authenticator(QObject *parent = nullptr);

  virtual void addAuthenticationToRequest(const QNetworkRequest *request);
};

} // namespace QRedmine

#pragma once

#include <QNetworkRequest>
#include <QObject>

namespace QRedmine {

class Authentication : public QObject {
  Q_OBJECT
public:
  explicit Authentication(QObject *parent = nullptr);

  virtual void addAuthenticationToRequest(QNetworkRequest *const request) = 0;
};

} // namespace QRedmine

#pragma once

#include <QNetworkRequest>
#include <QObject>
#include <qnetworkreply.h>
namespace QRedmine {

class Request : public QObject {
  Q_OBJECT
public:
  explicit Request(QObject *parent = nullptr);

protected:
  QNetworkRequest mRequest{};
  QNetworkReply *mReply{};

signals:
  void finished();
  void timeout();

private slots:
  virtual void requestFinished();
};

} // namespace QRedmine

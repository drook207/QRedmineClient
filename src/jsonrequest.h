#pragma once

#include "QJsonDocument"
#include "request.h"

namespace QRedmine {

class JsonRequest : public Request {
public:
  JsonRequest();

private:
  QJsonDocument mData{};
};

} // namespace QRedmine

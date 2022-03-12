#pragma once

#include <memory>

#include "network/engine/NetworkCommon.h"

namespace network {

class INetWorkSetting {
 public:
  virtual void setPort(const port_t port) = 0;
  virtual void setTcpProtocol(const TcpProtocol porotocol) = 0;
  virtual void setBufferSize(const size_t size) = 0;
};

}  // namespace network
#pragma once

#include <memory>

#include "network/engine/NetworkCommon.h"

namespace network {

class INetWorkSetting {
 public:
  virtual void setPort(const port_t port) = 0;
  virtual void setNetworkProtocol(const NetworkProtocol porotocol) = 0;
  virtual void setNetworkPacketSize(const size_t header,
                                    const size_t payload) = 0;
};

}  // namespace network
#pragma once

#include <string>

#include "network/engine/INetworkSetting.h"
#include "network/engine/NetworkEngineCore.h"

namespace network {

class NetworkEngineImpl : public INetWorkSetting {
 public:
  NetworkEngineImpl();
  virtual ~NetworkEngineImpl();

  void setPort(const port_t port) override;
  void setNetworkProtocol(const NetworkProtocol porotocol) override;
  void setNetworkPacketSize(const size_t header, const size_t payload) override;

  void run();

 private:
  NetWorkEngineCore mEngineCore;
};

}  // namespace network
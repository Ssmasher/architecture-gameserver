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
  void setTcpProtocol(const TcpProtocol porotocol) override;
  void setBufferSize(const size_t size) override;

  void run();

 private:
  NetWorkEngineCore mEngineCore;
};

}  // namespace network
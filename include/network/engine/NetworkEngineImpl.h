#pragma once

#include <string>

#include "network/engine/NetworkCommon.h"
#include "network/engine/NetworkEngineCore.h"

namespace network {

class NetworkEngineImpl {
 public:
  NetworkEngineImpl();
  virtual ~NetworkEngineImpl();

  void setPort(const port_t port);
  void setTcpProtocol(const TcpProtocol porotocol);

  void run();

 private:
  NetWorkEngineCore mEngineCore;
};

}  // namespace network
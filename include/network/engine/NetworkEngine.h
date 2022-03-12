#pragma once

#include <memory>
#include <string>

#include "network/engine/NetworkCommon.h"

namespace network {

class NetworkEngineImpl;

class NetworkEngine {
 public:
  explicit NetworkEngine(const port_t port, const TcpProtocol porotocol);
  virtual ~NetworkEngine();
  NetworkEngine(const NetworkEngine&& rhs) = delete;
  NetworkEngine& operator=(const NetworkEngine&& rhs) = delete;

  void setPort(const port_t port);
  void setTcpProtocol(const TcpProtocol porotocol);

  void run();

 private:
  std::shared_ptr<NetworkEngineImpl> mImpl;
};

}  // namespace network
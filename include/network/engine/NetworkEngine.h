#pragma once

#include <memory>
#include <string>

#include "network/engine/NetworkCommon.h"

namespace network {

class NetworkEngineImpl;

class NetworkEngine {
 public:
  explicit NetworkEngine(const port_t port, const NetworkProtocol porotocol);
  virtual ~NetworkEngine();
  NetworkEngine(const NetworkEngine&& rhs) = delete;
  NetworkEngine& operator=(const NetworkEngine&& rhs) = delete;

  void setNetworkPacketSize(const size_t header, const size_t payload);

  void run();

 private:
  std::unique_ptr<NetworkEngineImpl> mImpl;
};

}  // namespace network
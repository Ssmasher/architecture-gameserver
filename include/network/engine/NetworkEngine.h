#pragma once

#include <memory>
#include <string>

#include "network/engine/INetworkSetting.h"

namespace network {

class NetworkEngineImpl;

class NetworkEngine : public INetWorkSetting {
 public:
  explicit NetworkEngine(const port_t port, const TcpProtocol porotocol);
  virtual ~NetworkEngine();
  NetworkEngine(const NetworkEngine&& rhs) = delete;
  NetworkEngine& operator=(const NetworkEngine&& rhs) = delete;

  void setPort(const port_t port) override;
  void setTcpProtocol(const TcpProtocol porotocol) override;
  void setBufferSize(const size_t size) override;

  void run();

 private:
  std::shared_ptr<NetworkEngineImpl> mImpl;
};

}  // namespace network
#pragma once

#include <memory>
#include <string>

namespace network {

class NetworkEngineImpl;

class NetworkEngine {
 public:
  explicit NetworkEngine(const short port);
  virtual ~NetworkEngine();

  void setPort(const short port);

  void run();

 private:
  std::shared_ptr<NetworkEngineImpl> mImpl;
};

}  // namespace network
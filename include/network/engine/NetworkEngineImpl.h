#pragma once

#include <string>

#include "network/engine/NetworkEngineCore.h"

namespace network {

class NetworkEngineImpl {
 public:
  NetworkEngineImpl();
  virtual ~NetworkEngineImpl();

  void setPort(const short port);

  void run();

 private:
  NetWorkEngineCore mEngineCore;
};

}  // namespace network
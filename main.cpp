#include <future>

#include "common/logging.hpp"
#include "network/engine/NetworkEngine.h"

int main(int argc, char** argv) {
  network::NetworkEngine networkEngine(3000, network::TcpProtocol::V4);
  networkEngine.run();

  DEBUG("application is start")

  // #TODO main loop
  auto async = std::async([]() {
    while ((true)) {
    }
  });
  async.wait();

  return 0;
}
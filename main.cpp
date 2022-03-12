#include <future>

#include "common/logging.hpp"
#include "network/engine/NetworkEngine.h"

int main(int argc, char** argv) {
  network::NetworkEngine networkEngine(3000, network::TcpProtocol::V4);
  DEBUG("application is start")

  networkEngine.run();

  return 0;
}
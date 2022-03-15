#include <glibmm.h>

#include <future>

#include "common/logging.hpp"
#include "network/engine/NetworkEngine.h"

int main(int argc, char* argv[]) {
  Glib::RefPtr<Glib::MainLoop> mainLoop = Glib::MainLoop::create();

  network::NetworkEngine networkEngine(3000, network::NetworkProtocol::TCP_V4);
  networkEngine.run();

  DEBUG("application is start")

  mainLoop->run();

  return 0;
}
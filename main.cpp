#include <glibmm.h>

#include "common/logging.hpp"
#include "contents/UserClientHub.h"
#include "network/engine/NetworkEngine.h"

int main(int argc, char* argv[]) {
  Glib::RefPtr<Glib::MainLoop> mainLoop = Glib::MainLoop::create();

  UserClientHub clienthub;

  network::NetworkEngine networkEngine(3000, network::NetworkProtocol::TCP_V4);
  networkEngine.run();

  DEBUG("application is start")

  mainLoop->run();

  return 0;
}
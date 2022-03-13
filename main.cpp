#include <glibmm.h>

#include <future>

#include "common/logging.hpp"
#include "network/engine/NetworkEngine.h"

int main(int argc, char** argv) {
  Glib::RefPtr<Glib::MainLoop> mMainLoop = Glib::MainLoop::create();

  network::NetworkEngine networkEngine(3000, network::TcpProtocol::V4);
  networkEngine.run();

  DEBUG("application is start")

  mMainLoop->run();

  return 0;
}
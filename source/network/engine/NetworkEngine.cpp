#include "network/engine/NetworkEngine.h"

#include "common/logging.hpp"
#include "network/engine/NetworkEngineImpl.h"

network::NetworkEngine::NetworkEngine(const port_t port,
                                      const TcpProtocol porotocol)
    : mImpl(std::make_shared<NetworkEngineImpl>()) {
  mImpl->setPort(port);
  mImpl->setTcpProtocol(porotocol);
}

network::NetworkEngine::~NetworkEngine() {}

void network::NetworkEngine::setPort(const port_t port) {
  mImpl->setPort(port);
}

void network::NetworkEngine::setTcpProtocol(const TcpProtocol porotocol) {
  mImpl->setTcpProtocol(porotocol);
}

void network::NetworkEngine::run() { mImpl->run(); }
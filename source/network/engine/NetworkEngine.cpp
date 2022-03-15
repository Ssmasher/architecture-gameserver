#include "network/engine/NetworkEngine.h"

#include "common/logging.hpp"
#include "network/engine/NetworkEngineImpl.h"

network::NetworkEngine::NetworkEngine(const port_t port,
                                      const NetworkProtocol porotocol)
    : mImpl(std::make_unique<NetworkEngineImpl>()) {
  mImpl->setPort(port);
  mImpl->setNetworkProtocol(porotocol);
}

network::NetworkEngine::~NetworkEngine() {}

void network::NetworkEngine::setNetworkPacketSize(const size_t header,
                                                  const size_t payload) {
  mImpl->setNetworkPacketSize(header, payload);
}

void network::NetworkEngine::run() { mImpl->run(); }
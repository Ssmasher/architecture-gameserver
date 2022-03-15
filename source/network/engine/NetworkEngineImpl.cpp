#include "network/engine/NetworkEngineImpl.h"

network::NetworkEngineImpl::NetworkEngineImpl() {}

network::NetworkEngineImpl::~NetworkEngineImpl() {}

void network::NetworkEngineImpl::setPort(const port_t port) {
  mEngineCore.setPort(port);
}

void network::NetworkEngineImpl::setNetworkProtocol(
    const NetworkProtocol porotocol) {
  mEngineCore.setNetworkProtocol(porotocol);
}

void network::NetworkEngineImpl::setNetworkPacketSize(const size_t header,
                                                      const size_t payload) {
  mEngineCore.setNetworkPacketSize(header, payload);
}

void network::NetworkEngineImpl::run() { mEngineCore.run(); }
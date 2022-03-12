#include "network/engine/NetworkEngineImpl.h"

network::NetworkEngineImpl::NetworkEngineImpl() {}

network::NetworkEngineImpl::~NetworkEngineImpl() {}

void network::NetworkEngineImpl::setPort(const port_t port) {
  mEngineCore.setPort(port);
}

void network::NetworkEngineImpl::setTcpProtocol(const TcpProtocol porotocol) {
  mEngineCore.setTcpProtocol(porotocol);
}

void network::NetworkEngineImpl::setBufferSize(const size_t size) {
  mEngineCore.setBufferSize(size);
}

void network::NetworkEngineImpl::run() { mEngineCore.run(); }
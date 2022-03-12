#include "network/engine/NetworkEngineImpl.h"

network::NetworkEngineImpl::NetworkEngineImpl() {}

network::NetworkEngineImpl::~NetworkEngineImpl() {}

void network::NetworkEngineImpl::setPort(const short port) {
  mEngineCore.setPort(port);
}

void network::NetworkEngineImpl::run() { mEngineCore.run(); }
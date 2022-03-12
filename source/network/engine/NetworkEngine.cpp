#include "network/engine/NetworkEngine.h"

#include "common/logging.hpp"
#include "network/engine/NetworkEngineImpl.h"

network::NetworkEngine::NetworkEngine(const short port)
    : mImpl(std::make_shared<NetworkEngineImpl>()) {
  mImpl->setPort(port);
}

network::NetworkEngine::~NetworkEngine() {}

void network::NetworkEngine::setPort(const short port) { mImpl->setPort(port); }

void network::NetworkEngine::run() { mImpl->run(); }
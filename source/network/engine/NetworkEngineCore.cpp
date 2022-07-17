#include "network/engine/NetworkEngineCore.h"

#include "common/logging.hpp"
#include "network/engine/NetworkSession.h"
#include "network/engine/NetworkTcpSocket.h"
#include "network/engine/NetworkUdpSocket.h"

network::NetWorkEngineCore::NetWorkEngineCore() : mIoContext(1) {}

network::NetWorkEngineCore::~NetWorkEngineCore() {}

void network::NetWorkEngineCore::setPort(const port_t port) { mPort = port; }

void network::NetWorkEngineCore::setNetworkProtocol(
    const NetworkProtocol protocol) {
  mNetworkProtocol = protocol;
}

void network::NetWorkEngineCore::setNetworkPacketSize(const size_t header,
                                                      const size_t payload) {
  mHeaderSize = header;
  mPayloadSize = payload;
}

void network::NetWorkEngineCore::run() {
  if (!Thread::isRunning()) {
    bool isCreated = createSocket();
    if (isCreated) {
      Thread::run(std::bind(&NetWorkEngineCore::workThread, this));
      DEBUG("networkEngine is running");
    } else {
      ERROR("networkEngine is not working");
    }
  } else {
    DEBUG("networkEngine is already running");
  }
}

bool network::NetWorkEngineCore::createSocket() {
  DEBUG("create networkEngine socket");

  bool ret = true;

  if (nullptr == mNetworkSocket.get()) {
    switch (mNetworkProtocol) {
      case NetworkProtocol::TCP_V4:
      case NetworkProtocol::TCP_V6:
        mNetworkSocket = std::make_unique<NetworkTcpSocket>(
            mPort, mNetworkProtocol, mHeaderSize, mPayloadSize);
        break;
      case NetworkProtocol::UDP_V4:
      case NetworkProtocol::UDP_V6:
        mNetworkSocket =
            std::make_unique<NetworkUdpSocket>(mPort, mNetworkProtocol);
        break;
      default:
        ERROR("network protocol is not defined");
        ret = false;
        break;
    }

    if (ret) {
      ret = mNetworkSocket->create(mIoContext);
    } else {
      ERROR("network socket didn't created");
    }
  }

  return ret;
}

void network::NetWorkEngineCore::workThread() {
  try {
    DEBUG("workThread start");
    mIoContext.run();
  } catch (std::exception& e) {
    ERROR("IoContext Exception: " << e.what())
  }
}
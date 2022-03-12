#include "network/engine/NetworkEngineCore.h"

#include "common/logging.hpp"
#include "network/engine/NetworkSession.h"

network::NetWorkEngineCore::NetWorkEngineCore() : mIoContext(1) {}

network::NetWorkEngineCore::~NetWorkEngineCore() {}

void network::NetWorkEngineCore::setPort(const short port) { mPort = port; }

void network::NetWorkEngineCore::setTcpProtocol(TcpProtocol protocol) {
  mTcpProtocol = protocol;
}

void network::NetWorkEngineCore::run() {
  if (!mIsRunning) {
    bool isCreated = createAcceptor();
    if (true == isCreated) {
      try {
        doAccept();
        mIoContext.run();
      } catch (std::exception& e) {
        ERROR("IoContext Exception: " << e.what())
      }
    }

    mIsRunning = true;
    DEBUG("networkEngine is running");
  } else {
    DEBUG("networkEngine is already running");
  }
}

void network::NetWorkEngineCore::doAccept() {
  mAcceptor->async_accept([this](boost::system::error_code erroCode,
                                 boost::asio::ip::tcp::socket socket) {
    if (!erroCode) {
      std::make_shared<NetworkSession>(std::move(socket))->start();
    }

    doAccept();
  });
}

bool network::NetWorkEngineCore::createAcceptor() {
  if (nullptr == mAcceptor.get()) {
    switch (mTcpProtocol) {
      case TcpProtocol::V6: {
        mAcceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(
            mIoContext,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), mPort));
      } break;
      case TcpProtocol::V4:
      default: {
        mAcceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(
            mIoContext,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), mPort));
      } break;
    }
  }

  return (nullptr != mAcceptor.get());
}
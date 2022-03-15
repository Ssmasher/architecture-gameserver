#include "network/engine/NetworkTcpSoket.h"

#include "network/engine/NetworkSession.h"

network::NetworkTcpSoket::NetworkTcpSoket(port_t port, NetworkProtocol protocol)
    : mPort(port), mNetworkProtocol(protocol) {}

network::NetworkTcpSoket::~NetworkTcpSoket() {}

bool network::NetworkTcpSoket::create(boost::asio::io_context& ioContext) {
  if (nullptr == mAcceptor.get()) {
    switch (mNetworkProtocol) {
      case NetworkProtocol::TCP_V4: {
        mAcceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
            ioContext,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), mPort));
      } break;
      case NetworkProtocol::TCP_V6: {
        mAcceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
            ioContext,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), mPort));
      } break;
      default: {
      } break;
    }
  }

  if (nullptr != mAcceptor.get()) {
    doAccept();
  }

  return (nullptr != mAcceptor.get());
}

void network::NetworkTcpSoket::doAccept() {
  mAcceptor->async_accept([this](boost::system::error_code erroCode,
                                 boost::asio::ip::tcp::socket socket) {
    if (!erroCode) {
      std::make_shared<NetworkSession>(std::move(socket), 1024)->start();
    }

    doAccept();
  });
}

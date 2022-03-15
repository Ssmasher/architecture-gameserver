#pragma once

#include <boost/asio.hpp>

#include "network/engine/INetworkSocket.h"
#include "network/engine/NetworkCommon.h"

namespace network {

class NetworkTcpSocket : public INetworkSocket<boost::asio::io_context> {
 public:
  explicit NetworkTcpSocket(port_t port, NetworkProtocol protocol);
  virtual ~NetworkTcpSocket();

  bool create(boost::asio::io_context& ioContext) override;

 private:
  void doAccept();

 private:
  port_t mPort;
  NetworkProtocol mNetworkProtocol;
  std::unique_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;
};

}  // namespace network
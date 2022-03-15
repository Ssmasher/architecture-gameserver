#pragma once

#include <boost/asio.hpp>

#include "network/engine/INetworkSoket.h"
#include "network/engine/NetworkCommon.h"

namespace network {

class NetworkTcpSoket : public INetworkSoket<boost::asio::io_context> {
 public:
  explicit NetworkTcpSoket(port_t port, NetworkProtocol protocol);
  virtual ~NetworkTcpSoket();

  bool create(boost::asio::io_context& ioContext) override;

 private:
  void doAccept();

 private:
  port_t mPort;
  NetworkProtocol mNetworkProtocol;
  std::unique_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;
};

}  // namespace network
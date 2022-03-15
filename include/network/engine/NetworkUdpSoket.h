#pragma once

#include <boost/asio.hpp>

#include "network/engine/INetworkSoket.h"
#include "network/engine/NetworkCommon.h"

namespace network {

class NetworkUdpSoket : public INetworkSoket<boost::asio::io_context> {
 public:
  explicit NetworkUdpSoket(port_t port, NetworkProtocol protocol);
  virtual ~NetworkUdpSoket();

  bool create(boost::asio::io_context& ioContext) override;

 private:
 private:
  port_t mPort;
  NetworkProtocol mNetworkProtocol;
  std::unique_ptr<boost::asio::ip::udp::socket> mUdpSocket;
};

}  // namespace network
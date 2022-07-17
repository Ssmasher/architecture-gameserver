#pragma once

#include <boost/asio.hpp>

#include "network/engine/INetworkSocket.h"
#include "network/engine/NetworkCommon.h"

namespace network {

class NetworkUdpSocket : public INetworkSocket<boost::asio::io_context> {
 public:
  explicit NetworkUdpSocket(port_t port, NetworkProtocol protocol);
  virtual ~NetworkUdpSocket();

  bool create(boost::asio::io_context& ioContext) override;

 private:
  port_t mPort;
  NetworkProtocol mNetworkProtocol;
  std::unique_ptr<boost::asio::ip::udp::socket> mUdpSocket;
};

}  // namespace network
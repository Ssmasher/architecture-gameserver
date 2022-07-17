#include "network/engine/NetworkUdpSocket.h"

network::NetworkUdpSocket::NetworkUdpSocket(port_t port,
                                            NetworkProtocol protocol) {}

network::NetworkUdpSocket::~NetworkUdpSocket() {}

bool network::NetworkUdpSocket::create(boost::asio::io_context& ioContext) {
  // #TODO
  return false;
}
#pragma once

#include <boost/asio.hpp>
#include <mutex>
#include <unordered_map>

#include "network/engine/INetworkSocket.h"
#include "network/engine/NetworkCommon.h"
#include "network/engine/NetworkSession.h"

namespace network {

class NetworkTcpSocket : public INetworkSocket<boost::asio::io_context> {
 public:
  explicit NetworkTcpSocket(port_t port, NetworkProtocol protocol,
                            const size_t headerSize, const size_t payloadSize);
  virtual ~NetworkTcpSocket();

  bool create(boost::asio::io_context& ioContext) override;

 private:
  void doAccept();

  void addAliveSessionToList(const std::string& key,
                             const std::shared_ptr<NetworkSession>& session);
  void removeAliveSessionFromList(const std::string& key);
  const std::shared_ptr<NetworkSession> findSession(const std::string& key);
  bool isSessionInList(const std::string& key);

 private:
  std::mutex mMutex;
  port_t mPort;
  size_t mHeaderSize;
  size_t mPayloadSize;
  NetworkProtocol mNetworkProtocol;
  std::unique_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;
  std::unordered_map<std::string, std::shared_ptr<NetworkSession>> mSessionMap;
};

}  // namespace network
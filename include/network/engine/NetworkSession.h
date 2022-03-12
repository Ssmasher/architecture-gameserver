#pragma once

#include <boost/asio.hpp>
#include <vector>

namespace network {

class NetworkSession : public std::enable_shared_from_this<NetworkSession> {
 public:
  explicit NetworkSession(boost::asio::ip::tcp::socket&& socket) noexcept;
  virtual ~NetworkSession();

  void start();

 private:
  void readMessage();
  void sendMessage(size_t length);

 private:
  boost::asio::ip::tcp::socket mSocket;
  std::vector<char> mDataBuffer;
};

}  // namespace network
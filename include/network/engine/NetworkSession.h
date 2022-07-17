#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <vector>

namespace network {

class NetworkSession : public std::enable_shared_from_this<NetworkSession> {
  using DeleteCallAble = std::function<void(const std::string&)>;

 public:
  explicit NetworkSession(boost::asio::ip::tcp::socket&& socket,
                          size_t bufferSize) noexcept;
  virtual ~NetworkSession();

  void readMessage();
  void sendMessage(const std::vector<char>& data);

  void start();
  void close();

  std::string getID() const;
  void setID(const std::string& id);
  void setDeleteSessionCallback(const DeleteCallAble& callback);

 private:
  DeleteCallAble mDeleteSessionCallback;
  boost::asio::ip::tcp::socket mSocket;
  std::vector<char> mReceivedDataBuffer;
  std::string mSessionID;
};

}  // namespace network
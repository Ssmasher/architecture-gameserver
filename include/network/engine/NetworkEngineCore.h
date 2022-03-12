#pragma once

#include <boost/asio.hpp>

namespace network {

class NetWorkEngineCore {
 public:
  enum class TcpProtocol { V4, V6 };

  NetWorkEngineCore();
  virtual ~NetWorkEngineCore();
  NetWorkEngineCore(const NetWorkEngineCore&& rhs) = delete;
  NetWorkEngineCore& operator=(const NetWorkEngineCore&& rhs) = delete;

  void setPort(const short port);
  void setTcpProtocol(TcpProtocol protocol);

  void run();

 private:
  void doAccept();
  bool createAcceptor();

 private:
  bool mIsRunning = false;
  short mPort = 0;
  TcpProtocol mTcpProtocol = TcpProtocol::V4;
  boost::asio::io_context mIoContext;
  std::shared_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;
};

}  // namespace network

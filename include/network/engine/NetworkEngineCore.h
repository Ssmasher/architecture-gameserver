#pragma once

#include <boost/asio.hpp>

#include "common/Thread.h"
#include "network/engine/NetworkCommon.h"

namespace network {

class NetWorkEngineCore : public Thread {
 public:
  NetWorkEngineCore();
  virtual ~NetWorkEngineCore();
  NetWorkEngineCore(const NetWorkEngineCore&& rhs) = delete;
  NetWorkEngineCore& operator=(const NetWorkEngineCore&& rhs) = delete;

  void setPort(const port_t port);
  void setTcpProtocol(TcpProtocol protocol);

  void run();

 private:
  void workThread();

  void doAccept();
  bool createAcceptor();

 private:
  port_t mPort = 0;
  TcpProtocol mTcpProtocol = TcpProtocol::V4;
  boost::asio::io_context mIoContext;
  std::shared_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;
};

}  // namespace network

#pragma once

#include <boost/asio.hpp>

#include "common/Thread.h"
#include "network/engine/INetworkSetting.h"

namespace network {

class NetWorkEngineCore : public INetWorkSetting, Thread {
 public:
  NetWorkEngineCore();
  virtual ~NetWorkEngineCore();
  NetWorkEngineCore(const NetWorkEngineCore&& rhs) = delete;
  NetWorkEngineCore& operator=(const NetWorkEngineCore&& rhs) = delete;

  void setPort(const port_t port) override;
  void setTcpProtocol(const TcpProtocol protocol) override;
  void setBufferSize(const size_t size) override;

  void run();

 private:
  void workThread();

  void doAccept();
  bool createAcceptor();

 private:
  port_t mPort = 0;
  size_t mBufferSize = 1024;
  TcpProtocol mTcpProtocol = TcpProtocol::V4;
  boost::asio::io_context mIoContext;
  std::shared_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;
};

}  // namespace network

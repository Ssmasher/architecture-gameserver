#pragma once

#include <boost/asio.hpp>

#include "common/Thread.h"
#include "network/engine/INetworkSetting.h"
#include "network/engine/INetworkSocket.h"

namespace network {

class NetWorkEngineCore : public INetWorkSetting, private Thread {
 public:
  NetWorkEngineCore();
  virtual ~NetWorkEngineCore();
  NetWorkEngineCore(const NetWorkEngineCore&& rhs) = delete;
  NetWorkEngineCore& operator=(const NetWorkEngineCore&& rhs) = delete;

  void setPort(const port_t port) override;
  void setNetworkProtocol(const NetworkProtocol protocol) override;
  void setNetworkPacketSize(const size_t header, const size_t payload) override;

  void run();

 private:
  bool createEngineSocket();

  void workThread();

 private:
  port_t mPort = 0;
  size_t mHeaderSize = 0;
  size_t mPayloadSize = 1024;
  NetworkProtocol mNetworkProtocol = NetworkProtocol::TCP_V4;
  std::unique_ptr<INetworkSocket<boost::asio::io_context>> mNetworkSocket;
  boost::asio::io_context mIoContext;
};

}  // namespace network

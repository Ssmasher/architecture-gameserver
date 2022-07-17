#include "network/engine/NetworkSession.h"

#include "common/logging.hpp"
#include "network/engine/NetworkServiceTcpBridge.h"

constexpr static size_t VectorMaxLength =
    std::numeric_limits<std::vector<char>::size_type>::max();

network::NetworkSession::NetworkSession(boost::asio::ip::tcp::socket&& socket,
                                        size_t bufferSize) noexcept
    : mSocket(std::move(socket)), mDataBuffer(bufferSize, '\0') {}

network::NetworkSession::~NetworkSession() {
  DEBUG("TCP sessionID(" << mSessionID << ") is deleted")
}

void network::NetworkSession::start() {
  NetworkServiceTcpBridge::getInstance().emitConnectSession(mSessionID);
  readMessage();
}

void network::NetworkSession::readMessage() {
  auto self(shared_from_this());
  mSocket.async_receive(
      boost::asio::buffer(mDataBuffer.data(), mDataBuffer.size()),
      [this, self](boost::system::error_code erroCode, std::size_t length) {
        if (!erroCode) {
          NetworkServiceTcpBridge::getInstance().emitSessionEvent(mSessionID,
                                                                  mDataBuffer);
          sendMessage(length);
        } else {
          ERROR("reading in session is error. reason: " << erroCode.message())
          NetworkSession::close();
        }
      });
}

void network::NetworkSession::sendMessage(size_t length) {
  auto self(shared_from_this());
  boost::asio::async_write(
      mSocket, boost::asio::buffer(mDataBuffer.data(), length),
      [this, self](boost::system::error_code erroCode, std::size_t /*length*/) {
        if (!erroCode) {
          readMessage();
        } else {
          ERROR("writing in session is error. reason: " << erroCode.message())
          NetworkSession::close();
        }
      });
}

void network::NetworkSession::close() {
  DEBUG("close sessionID:" << mSessionID)
  mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
  mSocket.close();

  if (mDeleteSessionCallback) {
    mDeleteSessionCallback(mSessionID);
  }
}

void network::NetworkSession::setDeleteSessionCallback(
    const DeleteCallAble& callback) {
  mDeleteSessionCallback = callback;
}

std::string network::NetworkSession::getID() const { return mSessionID; }

void network::NetworkSession::setID(const std::string& id) { mSessionID = id; }
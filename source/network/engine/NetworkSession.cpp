#include "network/engine/NetworkSession.h"

#include "common/logging.hpp"

#define DEFAULT_DATA_BUFFER_SIZE 1024

constexpr static size_t VectorMaxLength =
    std::numeric_limits<std::vector<char>::size_type>::max();

network::NetworkSession::NetworkSession(
    boost::asio::ip::tcp::socket&& socket) noexcept
    : mSocket(std::move(socket)), mDataBuffer(DEFAULT_DATA_BUFFER_SIZE, '\0') {}

network::NetworkSession::~NetworkSession() {}

void network::NetworkSession::start() { readMessage(); }

void network::NetworkSession::readMessage() {
  auto self(shared_from_this());
  mSocket.async_read_some(
      boost::asio::buffer(mDataBuffer.data(), mDataBuffer.size()),
      [this, self](boost::system::error_code erroCode, std::size_t length) {
        if (!erroCode) {
          sendMessage(length);  // #TODO: this is for eco test
        } else {
          ERROR("reading in session is error. reason: " << erroCode.message())
        }
      });
}

void network::NetworkSession::sendMessage(size_t length) {
  auto self(shared_from_this());
  boost::asio::async_write(
      mSocket, boost::asio::buffer(mDataBuffer.data(), length),
      [this, self](boost::system::error_code erroCode, std::size_t /*length*/) {
        if (!erroCode) {
          readMessage();  // #TODO: this is for eco test
        } else {
          ERROR("writing in session is error. reason: " << erroCode.message())
        }
      });

  mDataBuffer.clear();  // #TODO: this is for eco test
}
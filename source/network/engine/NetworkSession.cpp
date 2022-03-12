#include "network/engine/NetworkSession.h"

#include "common/logging.hpp"

constexpr static size_t VectorMaxLength =
    std::numeric_limits<std::vector<char>::size_type>::max();

network::NetworkSession::NetworkSession(
    boost::asio::ip::tcp::socket&& socket) noexcept
    : mSocket(std::move(socket)), mData(VectorMaxLength, '\0') {}

network::NetworkSession::~NetworkSession() {}

void network::NetworkSession::start() { doRead(); }

void network::NetworkSession::doRead() {
  auto self(shared_from_this());
  mSocket.async_read_some(
      boost::asio::buffer(&mData[0], VectorMaxLength),
      [this, self](boost::system::error_code erroCode, std::size_t length) {
        if (!erroCode) {
          DEBUG("length: " << length << ", data: " << mData.data()
                           << ", size: " << mData.size())
          doWrite(length);
        }
      });
}

void network::NetworkSession::doWrite(size_t length) {
  auto self(shared_from_this());
  boost::asio::async_write(
      mSocket, boost::asio::buffer(mData.data(), length),
      [this, self](boost::system::error_code erroCode, std::size_t /*length*/) {
        if (!erroCode) {
          doRead();
        }
      });
}
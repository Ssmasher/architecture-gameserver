#include "network/engine/NetworkTcpSocket.h"

#include "common/logging.hpp"
#include "network/engine/NetworkServiceTcpBridge.h"

network::NetworkTcpSocket::NetworkTcpSocket(port_t port,
                                            NetworkProtocol protocol,
                                            const size_t headerSize,
                                            const size_t payloadSize)
    : mPort(port),
      mHeaderSize(headerSize),
      mPayloadSize(payloadSize),
      mNetworkProtocol(protocol) {
  NetworkServiceTcpBridge::getInstance().mSignalDeliverToClient.connect(
      [this](const std::string& sessionID, const std::vector<char>& data) {
        // working in main thread
        const auto& sharedSession = findSession(sessionID);
        if (sharedSession.get()) {
          sharedSession->sendMessage(data);
        }
      });
}

network::NetworkTcpSocket::~NetworkTcpSocket() {}

bool network::NetworkTcpSocket::create(boost::asio::io_context& ioContext) {
  DEBUG("create TCP socket");

  if (nullptr == mAcceptor.get()) {
    switch (mNetworkProtocol) {
      case NetworkProtocol::TCP_V4: {
        mAcceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
            ioContext,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), mPort));
      } break;
      case NetworkProtocol::TCP_V6: {
        mAcceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
            ioContext,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), mPort));
      } break;
      default: {
      } break;
    }
  }

  if (nullptr != mAcceptor.get()) {
    doAccept();
  }

  return (nullptr != mAcceptor.get());
}

void network::NetworkTcpSocket::doAccept() {
  mAcceptor->async_accept([this](boost::system::error_code erroCode,
                                 boost::asio::ip::tcp::socket socket) {
    if (!erroCode) {
      // #TODO: optimize session connection
      const std::string& sessionIP =
          socket.remote_endpoint().address().to_string();

      if (!isSessionInList(sessionIP)) {
        const auto& session = std::make_shared<NetworkSession>(
            std::move(socket), (mHeaderSize + mPayloadSize));

        addAliveSessionToList(sessionIP, session);

        DEBUG("sessionIP:" << sessionIP << " is start");

        session->setID(sessionIP);
        session->setDeleteSessionCallback([this](const std::string& key) {
          removeAliveSessionFromList(key);
        });

        session->start();
      } else {
        ERROR(sessionIP << " is exist. deny the connection");
      }

      doAccept();
    } else {
      ERROR("TCP socket accept error: " << erroCode);
    }
  });
}

void network::NetworkTcpSocket::addAliveSessionToList(
    const std::string& key, const std::shared_ptr<NetworkSession>& session) {
  std::lock_guard<std::mutex> lock(mMutex);
  if (mSessionMap.find(key) == mSessionMap.end()) {
    DEBUG("add TCP session key(" << key << ")");
    mSessionMap.emplace(key, session);
  } else {
    ERROR("TCP session key(" << key << ") is already exist");
  }
}

void network::NetworkTcpSocket::removeAliveSessionFromList(
    const std::string& key) {
  std::lock_guard<std::mutex> lock(mMutex);
  const auto iter = mSessionMap.find(key);
  if (iter != mSessionMap.end()) {
    DEBUG("remove TCP session key(" << key << ")");
    mSessionMap.erase(iter);
  } else {
    ERROR("TCP session key(" << key << ") is not exist");
  }
}

const std::shared_ptr<network::NetworkSession>
network::NetworkTcpSocket::findSession(const std::string& key) {
  std::lock_guard<std::mutex> lock(mMutex);
  std::shared_ptr<NetworkSession> ret;
  const auto iter = mSessionMap.find(key);
  if (iter != mSessionMap.end()) {
    ret = iter->second;
  } else {
    ERROR("TCP session key(" << key << ") is not exist");
  }

  return ret;
}

bool network::NetworkTcpSocket::isSessionInList(const std::string& key) {
  std::lock_guard<std::mutex> lock(mMutex);
  return (mSessionMap.find(key) != mSessionMap.end());
}
#include "network/UserClientTcpProxy.h"

#include "network/engine/NetworkServiceTcpBridge.h"

UserClientTcpProxy::UserClientTcpProxy() {}

UserClientTcpProxy::~UserClientTcpProxy() {}

bool UserClientTcpProxy::deliverToClient(const std::string& sessionID,
                                         const std::vector<char>& data) {
  NetworkServiceTcpBridge::getInstance().mSignalDeliverToClient(sessionID,
                                                                data);
  return true;
}
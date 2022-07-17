#include "network/UserClientTcpStub.h"
#include "network/engine/NetworkServiceTcpBridge.h"

UserClientTcpStub::UserClientTcpStub() {
  NetworkServiceTcpBridge::getInstance().setEventListener(this);
}

UserClientTcpStub::~UserClientTcpStub() {
  NetworkServiceTcpBridge::getInstance().removeEventListener(this);
}

bool UserClientTcpStub::operator==(const UserClientTcpStub& rhs) {
  return (this == &rhs);
}

void UserClientTcpStub::connectedClientID(const std::string& sessionID) {}

void UserClientTcpStub::receivedFromClient(const std::string& sessionID,
                                           const std::vector<char>& data) {}
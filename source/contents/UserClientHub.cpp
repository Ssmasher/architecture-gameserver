#include "contents/UserClientHub.h"

#include "common/logging.hpp"

UserClientHub::UserClientHub() : UserClientTcpStub(), UserClientTcpProxy() {}

UserClientHub::~UserClientHub() {}

void UserClientHub::connectedClientID(const std::string& sessionID) {
  DEBUG("new sessionID: " << sessionID)
}

void UserClientHub::receivedFromClient(const std::string& sessionID,
                                       const std::vector<char>& data) {
  DEBUG("received sessionID: " << sessionID << ", data: " << data.data())
}
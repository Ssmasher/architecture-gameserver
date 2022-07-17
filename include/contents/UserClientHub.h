#pragma once

#include "network/UserClientTcpProxy.h"
#include "network/UserClientTcpStub.h"

class UserClientHub : public UserClientTcpStub, UserClientTcpProxy {
 public:
  UserClientHub();
  virtual ~UserClientHub();

  virtual void connectedClientID(const std::string& sessionID) override;

  virtual void receivedFromClient(const std::string& sessionID,
                                  const std::vector<char>& data) override;
};
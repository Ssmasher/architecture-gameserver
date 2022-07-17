#pragma once

#include <string>
#include <vector>

class UserClientTcpStub {
 public:
  UserClientTcpStub();
  virtual ~UserClientTcpStub();
  UserClientTcpStub(const UserClientTcpStub& rhs) = default;
  UserClientTcpStub(const UserClientTcpStub&& rhs) = delete;
  UserClientTcpStub& operator=(const UserClientTcpStub&& rhs) = delete;

  bool operator==(const UserClientTcpStub& rhs);

  virtual void connectedClientID(const std::string& sessionID);

  virtual void receivedFromClient(const std::string& sessionID,
                                  const std::vector<char>& data);
};
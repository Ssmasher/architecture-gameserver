#pragma once

#include <string>
#include <vector>

class UserClientTcpProxy {
 public:
  UserClientTcpProxy();
  virtual ~UserClientTcpProxy();
  UserClientTcpProxy(const UserClientTcpProxy&& rhs) = delete;
  UserClientTcpProxy& operator=(const UserClientTcpProxy&& rhs) = delete;

  bool deliverToClient(const std::string& sessionID,
                       const std::vector<char>& data);
};
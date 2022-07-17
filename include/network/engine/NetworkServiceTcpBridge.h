#pragma once

#include <sigc++/sigc++.h>

#include <list>
#include <mutex>
#include <string>
#include <vector>

#include "network/UserClientTcpStub.h"

class NetworkServiceTcpBridge : public sigc::trackable {
 public:
  NetworkServiceTcpBridge();
  virtual ~NetworkServiceTcpBridge() = default;
  NetworkServiceTcpBridge(const NetworkServiceTcpBridge&& rhs) = delete;
  NetworkServiceTcpBridge& operator=(const NetworkServiceTcpBridge&& rhs) =
      delete;

  static NetworkServiceTcpBridge& getInstance();

  void setEventListener(UserClientTcpStub* object);
  void removeEventListener(const UserClientTcpStub* object);

 private:
  void slotConnectSession(const std::string& sessionID);
  void slotReceivedFromClient(const std::string& sessionID,
                              const std::vector<char>& data);

 public:
  // signal
  sigc::signal<void(const std::string&)> mSignalConnectSession;
  sigc::signal<void(const std::string&, const std::vector<char>&)>
      mSignalReceivedFromClient;
  sigc::signal<void(const std::string&, const std::vector<char>&)>
      mSignalDeliverToClient;

 private:
  std::mutex mMutex;
  std::list<UserClientTcpStub*> mObserverList;
};
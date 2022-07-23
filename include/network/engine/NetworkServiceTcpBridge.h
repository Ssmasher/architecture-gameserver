#pragma once

#include <glibmm.h>

#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

#include "network/UserClientTcpStub.h"

class NetworkServiceTcpBridge {
 public:
  NetworkServiceTcpBridge();
  virtual ~NetworkServiceTcpBridge() = default;
  NetworkServiceTcpBridge(const NetworkServiceTcpBridge&& rhs) = delete;
  NetworkServiceTcpBridge& operator=(const NetworkServiceTcpBridge&& rhs) =
      delete;

  static NetworkServiceTcpBridge& getInstance();

  void setEventListener(UserClientTcpStub* object);
  void removeEventListener(const UserClientTcpStub* object);

  void emitConnectSession(const std::string& sessionID);
  void emitReceivedFromClient(const std::string& sessionID,
                              const std::vector<char>& data);

 private:
  void dispatcher();

  void slotConnectSession(const std::string& sessionID);
  void slotReceivedFromClient(const std::string& sessionID,
                              const std::vector<char>& data);

 public:
  // signal
  sigc::signal<void(const std::string&, const std::vector<char>&)>
      mSignalDeliverToClient;

 private:
  std::mutex mMutex;
  Glib::Dispatcher mDispatcher;

  std::list<UserClientTcpStub*> mObserverList;

  std::queue<std::string> mQueueConnectSession;
  std::queue<std::pair<std::string, std::vector<char>>>
      mQueueReceivedFromClient;
};
#include "network/engine/NetworkServiceTcpBridge.h"

#include <algorithm>

#include "common/logging.hpp"

NetworkServiceTcpBridge::NetworkServiceTcpBridge() {
  mSignalConnectSession.connect(
      sigc::mem_fun(this, &NetworkServiceTcpBridge::slotConnectSession));

  mSignalSessionEvent.connect(
      [this](const std::string& sessionID, const std::vector<char>& data) {
        slotSessionEvent(sessionID, data);
      });
}

NetworkServiceTcpBridge& NetworkServiceTcpBridge::getInstance() {
  static NetworkServiceTcpBridge instance;
  return instance;
}

void NetworkServiceTcpBridge::setEventListener(UserClientTcpStub* object) {
  std::lock_guard<std::mutex> lock(mMutex);
  const auto iter =
      std::find(mObserverList.begin(), mObserverList.end(), object);
  if (iter == mObserverList.end()) {
    mObserverList.push_back(object);
  }
}

void NetworkServiceTcpBridge::removeEventListener(
    const UserClientTcpStub* object) {
  std::lock_guard<std::mutex> lock(mMutex);
  const auto iter =
      std::find(mObserverList.begin(), mObserverList.end(), object);
  if (iter != mObserverList.end()) {
    mObserverList.erase(iter);
  }
}

void NetworkServiceTcpBridge::emitConnectSession(const std::string& sessionID) {
  mSignalConnectSession(sessionID);
}

void NetworkServiceTcpBridge::emitSessionEvent(const std::string& sessionID,
                                               const std::vector<char>& data) {
  mSignalSessionEvent(sessionID, data);
}

void NetworkServiceTcpBridge::slotConnectSession(const std::string& sessionID) {
  for (auto iter = mObserverList.begin(); iter != mObserverList.end(); ++iter) {
    if (*iter != nullptr) {
      (*iter)->connectedClientID(sessionID);
    } else {
      ERROR("this iter is nullptr. remove this iter")
      iter = mObserverList.erase(iter);
    }
  }
}

void NetworkServiceTcpBridge::slotSessionEvent(const std::string& sessionID,
                                               const std::vector<char>& data) {
  for (auto iter = mObserverList.begin(); iter != mObserverList.end(); ++iter) {
    if (*iter != nullptr) {
      (*iter)->receivedFromClient(sessionID, data);
    } else {
      ERROR("this iter is nullptr. remove this iter")
      iter = mObserverList.erase(iter);
    }
  }
}
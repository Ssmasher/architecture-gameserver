#include "network/engine/NetworkServiceTcpBridge.h"

#include <algorithm>

#include "common/logging.hpp"

NetworkServiceTcpBridge::NetworkServiceTcpBridge() {
  mDispatcher.connect(
      sigc::mem_fun(*this, &NetworkServiceTcpBridge::dispatcher));
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
  std::lock_guard<std::mutex> lock(mMutex);
  mQueueConnectSession.emplace(sessionID);
  mDispatcher.emit();
}

void NetworkServiceTcpBridge::emitReceivedFromClient(
    const std::string& sessionID, const std::vector<char>& data) {
  std::lock_guard<std::mutex> lock(mMutex);
  mQueueReceivedFromClient.emplace(std::make_pair(sessionID, data));
  mDispatcher.emit();
}

void NetworkServiceTcpBridge::dispatcher() {
  // working in main thread
  std::lock_guard<std::mutex> lock(mMutex);

  if (!mQueueConnectSession.empty()) {
    slotConnectSession(mQueueConnectSession.front());
    mQueueConnectSession.pop();
  }

  if (!mQueueReceivedFromClient.empty()) {
    slotReceivedFromClient(mQueueReceivedFromClient.front().first,
                           mQueueReceivedFromClient.front().second);
    mQueueReceivedFromClient.pop();
  }
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

void NetworkServiceTcpBridge::slotReceivedFromClient(
    const std::string& sessionID, const std::vector<char>& data) {
  for (auto iter = mObserverList.begin(); iter != mObserverList.end(); ++iter) {
    if (*iter != nullptr) {
      (*iter)->receivedFromClient(sessionID, data);
    } else {
      ERROR("this iter is nullptr. remove this iter")
      iter = mObserverList.erase(iter);
    }
  }
}
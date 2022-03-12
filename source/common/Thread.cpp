#include "common/Thread.h"

#include "common/logging.hpp"

Thread::Thread() {}

Thread::~Thread() { join(); }

void Thread::run(const std::function<void()>& workFunction) {
  if (workFunction) {
    if (!isRunning()) {
      mThread = std::make_shared<std::thread>(workFunction);
    }
  }
}

void Thread::join() {
  if (isRunning()) {
    try {
      mThread->join();
    } catch (const std::exception& e) {
      ERROR("Thread::join is error. reason: " << e.what())
    }
  }
}

bool Thread::isRunning() { return (nullptr != mThread.get()); }
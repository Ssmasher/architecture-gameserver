#pragma once

#include <functional>
#include <memory>
#include <thread>

class Thread {
 public:
  explicit Thread();
  virtual ~Thread();

  void run(const std::function<void()>& workFunction);
  void join();
  bool isRunning();

 private:
  std::shared_ptr<std::thread> mThread;
};
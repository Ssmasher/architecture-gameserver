#pragma once

#include <iostream>
#include <thread>

#define DEBUG(content)                                                       \
  std::cout << "[Thread::" << std::this_thread::get_id() << "] " << __FILE__ \
            << "::" << __FUNCTION__ << "::line_" << __LINE__                 \
            << "::" << content << std::endl;

#define ERROR(content) DEBUG(content)
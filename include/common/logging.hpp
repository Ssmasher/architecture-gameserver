#pragma once

// #include <stdio.h>

#include <iostream>

#define DEBUG(content)                                                   \
  std::cout << __FILE__ << "::" << __FUNCTION__ << "::line_" << __LINE__ \
            << "::" << content << std::endl;

#define ERROR(content) DEBUG(content)
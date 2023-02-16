#include <functional>

#pragma once

struct Task { // 1st version , only support funcs with no return and no arguments
 public:
  Task() = default;
  ~Task() = default;
  std::function<void(void)> task_;
};
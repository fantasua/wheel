#include <functional>

#pragma once

// 1st version , only support funcs with no return and no
// arguments
struct Task {
  Task(std::function<void(void)> task) : task_(task) {}
  std::function<void(void)> task_;
};
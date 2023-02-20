#include <functional>

#pragma once

// 1st version , only support funcs with no return and no
// arguments
struct Task {
  Task(std::function<void(void)> task) : task_(task) {}
  // task has two arguments
  // first void* is return value wrapped in void*
  // second void* is arguments wrapped in void*
  std::function<void(void)> task_;
};
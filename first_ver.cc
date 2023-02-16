#pragma once

#include "first_ver.h"

MyThread::MyThread() {}
MyThread::~MyThread() {}

bool MyThread::StartThread() {
  is_running_ = true;
  return true;
}
bool MyThread::StopThread() {
  is_running_ = false;
  return true;
}

void MyThread::loop_func() { return; }

MyPool::MyPool(int thread_num) {
  thread_num_ = thread_num;
  threads_.resize(thread_num_);
}

MyPool::~MyPool(){

}

MyPool &MyPool::Get() {
  static std::shared_ptr<MyPool> my_pool;
  if (!my_pool) {
    my_pool = std::make_shared<MyPool>();
  }
  return *my_pool;
}
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include "my_queue.h"
#include "my_task.h"

#pragma once

class BaseThread {
 public:
  BaseThread();
  BaseThread(BaseThread &) = delete;  // no copyable
  BaseThread(BaseThread &&);          // movable
  ~BaseThread();

 public:
  bool start_thread();
  void stop_thread();
  bool is_running() { return running_; }
  void add_task(std::shared_ptr<Task> task) {
    std::lock_guard<std::mutex> lk(mutex_);
    task_queue_.push_back(task);
    cv_.notify_one();
  }

  void join() { thread_->join(); }

 protected:
  // what you do in one loop
  // it is the function that in the thread loop
  void loop_func();

 private:
  // identify whether the thread is running
  bool running_;

  std::mutex mutex_;
  std::condition_variable cv_;
  std::shared_ptr<std::thread> thread_;

  // put task queue in thread
  // so that we don't have to lock it
  QueueWithoutLock task_queue_;
};

class MasterThread : public BaseThread {};

class SlaveThread : public BaseThread {};

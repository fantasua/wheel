#include "my_queue.h"

#pragma once

class BaseThread {
 public:
  BaseThread();
  BaseThread(BaseThread &) = delete;  // no copyable
  BaseThread(BaseThread &&);          // movable
  ~BaseThread();

 public:
  bool start_thread();
  bool stop_thread();
  bool is_running() { return running_; }

 protected:
  virtual void loop_func() = 0;  // main loop func

 private:
  // identify whether the thread is running
  bool running_;

  // put task queue in thread
  // so that we don't have to lock it
  QueueWithoutLock task_queue_;
};

class MasterThread : public BaseThread {};

class SlaveThread : public BaseThread {};

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "my_queue.h"
#include "my_task.h"

#ifdef TEST
#include <iostream>
#endif

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

  int report_queue_load() {
    std::lock_guard<std::mutex> lk(mutex_);
#ifdef TEST
    std::cout << "queue_len " << task_queue_.size() << std::endl;
#endif
    return task_queue_.size();
    cv_.notify_all();
  }

  void join() { thread_->join(); }

 protected:
  // what you do in one loop
  // it is the function that in the thread loop
  virtual void loop_func();

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

// serve as a task dispatcher
// manage the thread pool and dispatch tasks from the task queue to other worker
// slave threads
class MasterThread : public BaseThread {
 public:
  MasterThread(int slave_num);
  MasterThread(MasterThread &) = delete;
  ~MasterThread();

 public:
  virtual void loop_func();


 public:
  void add_slave_thread(std::shared_ptr<std::thread> slave);
  void delete_slave_thread(int slave_id);

 public:
  void add_task(std::shared_ptr<Task> task);

 private:
  void dispatch_task();
  void monitor_task();

 private:
  int thread_num;
  std::unordered_map<int, std::shared_ptr<std::thread>> slave_threads_;

 private:
  // monitor all the slave thread workload
  std::shared_ptr<std::thread> slave_work_load_monitor_;
  // the master thread uses thread_ from BaseThread to dispatch tasks to salves
};

// do the task that are dispatched to slave threads
class SlaveThread : public BaseThread {
 
};

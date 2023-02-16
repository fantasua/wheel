#include <memory>
#include <mutex>
#include <queue>

#include "my_task.h"

#pragma once

struct BaseQueue {
  BaseQueue() {}
  virtual ~BaseQueue() {}

  virtual std::shared_ptr<Task> pop_front() {
    if (is_empty()) {
      return nullptr;
    }
    std::shared_ptr<Task> res = queue_.front();
    queue_.pop();
    return res;
  }
  virtual bool push_back(std::shared_ptr<Task> task) { queue_.push(task); }
  virtual bool is_empty() { return queue_.empty(); }

 private:
  std::queue<std::shared_ptr<Task>> queue_;
};

class QueueWithoutLock : public BaseQueue {
 public:
  QueueWithoutLock() {}
  virtual ~QueueWithoutLock() {}

 public:
  virtual std::shared_ptr<Task> pop_front() { return BaseQueue::pop_front(); }
  virtual bool push_back(std::shared_ptr<Task> task) {
    return BaseQueue::push_back(task);
  }
  bool is_empty() { return BaseQueue::is_empty(); }
};

class QueueWithLock : public BaseQueue {
 public:
  QueueWithLock() {}
  virtual ~QueueWithLock() {}

 public:
  virtual std::shared_ptr<Task> pop_front() {
    std::lock_guard<std::mutex> lk(mutex_);
    return BaseQueue::pop_front();
  }
  virtual bool push_back(std::shared_ptr<Task> task) {
    std::lock_guard<std::mutex> lk(mutex_);
    return BaseQueue::push_back(task);
  }
  bool is_empty() {
    std::lock_guard<std::mutex> lk(mutex_);
    return BaseQueue::is_empty();
  }

 private:
  std::mutex mutex_;
};

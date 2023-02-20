#include "my_thread.h"

BaseThread::BaseThread() {}

BaseThread::BaseThread(BaseThread &&input) {}

BaseThread::~BaseThread() {}

bool BaseThread::start_thread() {
  running_ = true;
  auto task = [this]() { loop_func(); };
  thread_ = std::make_shared<std::thread>(task);
  return true;
}

void BaseThread::loop_func() {
  while (running_) {
    std::unique_lock<std::mutex> lk(mutex_);
    cv_.wait(lk, [this]() -> bool {
      return !task_queue_.is_empty() || !running_;
    });
    if (!running_) {
      return;
    }
    // do something
    std::shared_ptr<Task> task_ptr = task_queue_.pop_front();
    task_ptr->task_();
  }
  return;
}

void BaseThread::stop_thread() {
  std::lock_guard<std::mutex> lk(mutex_);
  running_ = false;
  cv_.notify_all();
}

MasterThread::MasterThread(int slave_num) : thread_num(slave_num) {

}
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

typedef void*(*MyFuncType)(void*);
using Task = MyFuncType;
//using Task = std::function<void* (void*)>;

// TODO
//class Task{}; // task processed by threads in thread pool

class MyThread {
 public:
  MyThread();
  ~MyThread();

 public:
  bool StartThread();
  bool StopThread();

 private:
  void loop_func();
 private:
  bool is_running_;
};

class MyPool {
 public:
  static MyPool &Get();

  MyPool(int threads_num);
  ~MyPool();

 public:
  int RunPool();                  // start thread pool
  int AddTask(Task &input_task);  // add task to thread pool

 private:
  int thread_num_;
  std::vector<MyThread> threads_;  // contains all the threads
  std::queue<Task> task_queue_;
};

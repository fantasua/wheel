#include <iostream>
#include <chrono>
#include <unistd.h>

#include "my_task.h"
#include "my_thread.h"


int main() {
  BaseThread b;
  std::shared_ptr<Task> task =
      std::make_shared<Task>([]() { std::cout << "TEST" << std::endl; });

  b.start_thread();
  for (int i = 0; i < 100; ++i) {
    b.add_task(task);
  }
  std::thread q = std::thread([&b]() {
    while (1) {
      b.report_queue_load();
      sleep(1);
    }
  });

  sleep(4);
  b.join();
  q.join();
  
  return 0;
}
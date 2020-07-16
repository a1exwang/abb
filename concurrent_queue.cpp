#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

class Queue {
 public:
  Queue(size_t max_size) :max_size(max_size) { }
  void push(int value) {
    std::unique_lock ul(m);
    while (is_full()) {
      element_popped.wait(ul);
    }
    q.push(value);
    element_pushed.notify_one();
  }
  int pop() {
    std::unique_lock ul(m);
    while (q.empty()) {
      element_pushed.wait(ul);
    }
    auto ret = q.front();
    q.pop();

    element_popped.notify_one();
    return ret;
  }
 private:
  bool is_full() const {
    return q.size() >= max_size;
  }
  std::mutex m;
  std::condition_variable element_pushed, element_popped;

  std::queue<int> q;
  size_t max_size;
};

int main() {
  int consumers = 10;
  int producers = 10;
  int q_size = 10;
  int job_count = 2000;

  Queue q(q_size);
  std::vector<std::thread> threads;
  std::atomic<int> counter{0};

  std::vector<std::atomic<int>> jobs(job_count);
  for (auto &job : jobs) {
    job = 0;
  }

  for (int i = 0; i < producers; i++) {
    threads.emplace_back([&, i]() {
      while (true) {
        auto job_id = counter.fetch_add(1);

        q.push(job_id);
        if (job_id == job_count) {
          // push -1
          for (int k = 0; k < consumers; k++) {
            q.push(-1);
          }
        }
        if (job_id >= job_count) {
          break;
        }
      }
    });
  }

  for (int i = 0; i < consumers; i++) {
    threads.emplace_back([&, i]() {
      while (true) {
        auto job_id = q.pop();
        if (job_id == -1) {
          break;
        } else {
          jobs[job_id].fetch_add(1);
        }
      }
    });
  }
  for (auto &t : threads) {
    t.join();
  }

  for (size_t job_id = 0; job_id < jobs.size(); job_id++) {
    if (jobs[job_id] != 1) {
      cerr << "Error: jobs[" << job_id << "] == " << jobs[job_id] << " (!=1) " << endl;
      abort();
    }
  }
  std::cout << "All tests have passed" << std::endl;
}
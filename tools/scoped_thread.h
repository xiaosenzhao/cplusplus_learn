#include <thread>

class ScopedThread {
  std::thread t;
 public:
  explicit ScopedThread(std::thread t_) : t(std::move(t_)) {
    if (!t.joinable()) {
      throw std::logic_error("no thread");
    }
  }
  ~ScopedThread() {
    t.join();
  }

  ScopedThread(const ScopedThread&) = delete;
  ScopedThread& operator=(const ScopedThread&) = delete;
};

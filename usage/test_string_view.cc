#include <string_view>
#include <string>
#include <iostream>
#include <chrono>

class Timer {
 public:
  Timer(const std::string& title) : title(title) {
    m_start_ = std::chrono::high_resolution_clock::now();
  }

  ~Timer() {
    stop();
  }

  void stop() {
    m_stop_ = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(m_stop_ - m_start_);
    std::cout << title << " " << ms.count() << "ms" << std::endl;
  }
 private:
  std::string title;
  std::chrono::high_resolution_clock::time_point m_start_;
  std::chrono::high_resolution_clock::time_point m_stop_;
};

void FuncWithString(const std::string& string) {
}

void FuncWithString(const std::string_view& string) {
}

int main(void) {
  Timer timer("std::string");
  for (int i = 0; i < 1000000; i++) {
    std::string name = "zhangsan";
    std::string firstname = name.substr(0, 5);
    std::string lastname = name.substr(5, 3);
    FuncWithString(firstname);
    FuncWithString(lastname);
  }
  timer.stop();

  Timer timer1("std::string_view");
  for (int i = 0; i < 1000000; i++) {
    const char* name = "zhangsan";
    std::string_view firstname = std::string_view(name, 5);
    std::string_view lastname = std::string_view(name + 5, 3);
    FuncWithString(firstname);
    FuncWithString(lastname);
  }
  timer1.stop();
  return 0;
}


#include <iostream>
#include <memory>

// 限制对象数量
template <class ToBeLimited, uint32_t maxInstance>
class LimitNoOfInstances {
 public:
  static std::atomic<uint32_t> cnt;

  LimitNoOfInstances() {
    if (cnt >= maxInstance) {
      std::cout << "too many instaces" << std::endl;
    }
    cnt += 1;
  }
  ~LimitNoOfInstances() { cnt -= 1; }
};

class One : public LimitNoOfInstances<One, 1> {};

class Two : public LimitNoOfInstances<Two, 2> {};

template <class T, uint32_t maxNoOfInstance>
std::atomic<uint32_t> LimitNoOfInstances<T, maxNoOfInstance>::cnt = 0;

int main(void) {
  Two a, b;
  One c;
  One d;
  return 0;
}
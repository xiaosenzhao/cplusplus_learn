#include <iostream>

template <typename T>
class NoDestructor {
 public:
  template <typename... Args>
  explicit NoDestructor(Args&&... args) {
    std::cout << "NoDestructor Constructor" << std::endl;
    new (storage_) T(std::forward<Args>(args)...);
  }

  explicit NoDestructor(const T& x) { new (storage_) T(x); }
  explicit NoDestructor(T&& x) { new (storage_) T(std::move(x)); }

  NoDestructor(const NoDestructor&) = delete;
  NoDestructor& operator=(const NoDestructor&) = delete;

  ~NoDestructor() = default;

  const T& operator*() const { return *get(); }
  T& operator->() { return get(); }

  const T* get() const { return reinterpret_cast<const T*>(storage_); }
  T* get() { return reinterpret_cast<T*>(storage_); }

 private:
  alignas(T) char storage_[sizeof(T)];
};

class Foo {
 public:
  Foo(const std::string& name) {
    a = name;
    b.reserve(10);
    for (int i = 0; i < 10; ++i) {
      b.emplace_back(i);
    }
  }

  ~Foo() { std::cout << "Foo Destructor" << std::endl; }

 private:
  std::string a;
  std::vector<int> b;
};

int main(void) {
  NoDestructor<Foo> bar("hello world");
  return 0;
}
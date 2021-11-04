#include <iostream>
#include <functional>
#include <map>
#include <string>

struct CallBase {
  virtual ~CallBase() {}
};

template <typename Ret, typename... Arg>
struct Caller : public CallBase {
  std::function<Ret(Arg...)> f;
  Caller(std::function<Ret(Arg...)> ff) : f(ff) {}
  Ret call(const Arg&... arg) const {
    return f(arg...);
  }
};

struct CallHelper;

template <typename Ret>
struct CallHelperRvSp {
  const CallHelper* helper;
  CallHelperRvSp(const CallHelper* ch) : helper(ch) {}
  template <typename... Arg>
  Ret operator()(const Arg&... arg) const;
};

struct CallHelper {
  CallBase* base;
  CallHelper(CallBase* p) : base(p) {}
  template <typename Ret, typename... Arg>
  Ret operator()(const Arg&... arg) const {
    auto caller = dynamic_cast<Caller<Ret, Arg...>*>(base);
    if (caller != nullptr) {
      return caller->call(arg...);
    } else {
      throw "Type not match";
    }
  }
  template <typename Type>
  CallHelperRvSp<Type> Ret() const {
    return CallHelperRvSp<Type>(this);
  }
};

template <typename Ret>
template <typename... Arg>
Ret CallHelperRvSp<Ret>::operator()(const Arg&... arg) const {
  return helper->operator()<Ret>(arg...);
}

std::map<std::string, CallBase*> fs;

template <typename Ret, typename... Arg>
void insert(const std::string& name, std::function<Ret(Arg...)> f) {
  fs[name] = new Caller<Ret, Arg...>(f);
}

CallHelper find(const std::string& name) {
  return CallHelper(fs[name]);
}

int main(void) {
  insert("add", std::function<int(int, int)>(std::plus<int>()));
  auto f = find("add").Ret<int>();
  std::cout << f(1, 2) << std::endl;
  return 0;
}

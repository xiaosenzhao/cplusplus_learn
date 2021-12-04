#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <chrono>
#include <thread>

void fatalError(const std::string& error_msg) {
  std::cout << error_msg << std::endl;
}

class Context {
 public:
  Context(int timeout) : _timeout(timeout) {
    if (::pipe(_pfd) == -1) {
      fatalError("syscall pipe error");
    }
  }

  void done() {
    ::close(_pfd[1]);
  }

  bool wait() {
    int epfd = ::epoll_create(1);
    if (epfd < 0) {
      fatalError("syscall epoll_create error");
    }
    struct epoll_event ev;
    ev.data.fd = _pfd[0];
    ev.events = EPOLLRDHUP;
    if (::epoll_ctl(epfd, EPOLL_CTL_ADD, _pfd[0], &ev) < 0){
      fatalError("syscall epoll_ctl error");
    }
    int n = ::epoll_wait(epfd, &ev, 1, _timeout);
    ::close(_pfd[0]);
    ::close(epfd);
    if (n == -1) {
      fatalError("sysncall epoll_wait error");
    }
    return n == 1;
  }
 private:
  int _pfd[2];
  int _timeout;
};

class ThreadWithCtx {
 public:
  typedef void*(*ThreadFuncPtr)(void*);

  ThreadWithCtx(ThreadFuncPtr f, void* arg, Context* ctx) : _f(f), _arg(arg), _ctx(ctx) {}

  struct ArgWithCtx {
    ThreadWithCtx::ThreadFuncPtr _f;
    void* _arg;
    Context* _ctx;
    ArgWithCtx(ThreadFuncPtr f, void* arg, Context* ctx) : _f(f), _arg(arg), _ctx(ctx) {}
  };

  ThreadFuncPtr _f;
  void* _arg;
  Context* _ctx;

  bool run() {
    pthread_t thr;
    ArgWithCtx argCtx(_f, _arg, _ctx);
    if (::pthread_create(&thr, NULL, _thread_wrapper, (void*)(&argCtx)) < 0) {
      fatalError("syscall phtread_create error");
    }
    bool ok = _ctx->wait();
    if (!ok && ::pthread_cancel(thr) < 0) {
      fatalError("syscall phtread_cancel error");
    }
    if (::pthread_join(thr, NULL) < 0) {
      fatalError("syscall phread_join error");
    }
    return ok;
  }

  static void* _thread_wrapper(void* arg) {
    ArgWithCtx* ptr = static_cast<ArgWithCtx*>(arg);
    ptr->_f(ptr->_arg);
    ptr->_ctx->done();
    return NULL;
  }
};

struct SimpleArgs {
  int a;
  int b;
  int ret;
  SimpleArgs(int a, int b) : a(a), b(b) {}
};

void* simple_func(void* arg) {
  SimpleArgs* ptr = static_cast<SimpleArgs*>(arg);
  std::cout << "Thread will sleep:" << ptr->a << " millseconds" << std::endl;
  std::cout << "Argument b is " << ptr->b << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(ptr->a));
  ptr->ret = ptr->a + ptr->b;
  return NULL;
}

int main() {
  int num = 10000;
  Context ctx(num);
  std::cout << "Context timeout is " << num << " millseconds" << std::endl;

  SimpleArgs arg(3000, 8888);
  ThreadWithCtx t(simple_func, &arg, &ctx);
  if (t.run()) {
    std::cout << "Thread ends normally, return: " << arg.ret << std::endl;
  } else {
    std::cout << "Thread timeout and have been canceled" << std::endl;
  }
  return 0;
}


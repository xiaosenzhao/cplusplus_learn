//g++ ThreadPool.cpp -o test --std=c++11 -lpthread
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <iostream>

class ThreadPool {
public:
    ThreadPool(size_t);

    template <typename F, class... Args>
    auto enqueue(F&& f, Args&&... args) ->
        std::future<typename std::result_of<F(Args...)>::type>;

    ~ThreadPool();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

inline ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for (size_t i = 0; i < threads; i++) {
        workers.emplace_back(
                [this]{
                    while (true) {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            // wait(lock, pre)
                            // when wait, blocked when pre is false
                            // when notify, unblocked when pre is true
                            this->condition.wait(lock,
                                    [this]{ return this->stop || !this->tasks.empty(); });
                            if (this->stop && this->tasks.empty()) {
                                return;
                            }
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }
                        task();
                    }
                }
        );
    }
}

template <typename F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) ->
    std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>> (
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop) {
            throw std::runtime_error("enqueue on stoped thread pool");
        }
        tasks.emplace([task]() {(*task)();});
    }
    condition.notify_one();
    return res;
}

inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (auto& thread : workers) {
        thread.join();
    }
    std::cout << "thread pool end" << std::endl;
}

int echo() {
    std::thread::id tid = std::this_thread::get_id();
    std::cout << tid << std::endl;
    return 0;
};

int main(void) {
    ThreadPool tp(4);
    std::vector<std::future<int>> results;

    results.emplace_back(tp.enqueue(std::function<int()>(echo)));
    results.emplace_back(tp.enqueue(std::function<int()>(echo)));
    results.emplace_back(tp.enqueue(std::function<int()>(echo)));
    results.emplace_back(tp.enqueue(std::function<int()>(echo)));
    results.emplace_back(tp.enqueue(std::function<int()>(echo)));
    results.emplace_back(tp.enqueue(std::function<int()>(echo)));

    for (auto& result : results) {
        std::cout << result.get() << ' ';
    }
    std::cout << std::endl;

    return 0;
}


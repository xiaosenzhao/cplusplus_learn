#include <atomic>
#include <iostream>

template <typename T>
class PushOnlyStack {
public:
    PushOnlyStack() {
        _head.store(nullptr, std::memory_order_relaxed);
    }

    void push(T* node) {
        T* head = _head.load(std::memory_order_relaxed);
        node->next = head;
        while (!_head.compare_exchange_weak(
                    head, node, std::memory_order_relaxed)) {
                node->next = head;
        }
    }

    T* release() {
        return _head.exchange(nullptr, std::memory_order_relaxed);
    }

private:
    std::atomic<T*> _head;
};

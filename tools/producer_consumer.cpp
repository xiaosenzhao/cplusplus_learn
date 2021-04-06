#include <thread>
#include <future>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <chrono>

//单生产者-单消费者
//spsm

static const int kItemRepositorySize = 10; //buffer size
static const int kItemsToProduce = 1000; // how many items plan to produce

struct ItemRepository {
    int item_buffer[kItemRepositorySize]; //ring buffer
    size_t read_position;
    size_t write_position;
    std::mutex mtx;
    std::condition_variable repo_not_full; //条件变量，指示缓冲区不满
    std::condition_variable repo_not_empty; //条件变量，指示缓冲区不空

    ItemRepository() {
        read_position = 0;
        write_position = 0;
    }
} gItemRepository;

typedef struct ItemRepository ItemRepository;

void produce(ItemRepository* it, int item) {
    std::unique_lock<std::mutex> lock(it->mtx);
    while (((it->write_position + 1) % kItemRepositorySize) == it->read_position) {
        // buffer is full, just wait
        std::cout << "Producer is waitting for an empty slot..." << std::endl;
        it->repo_not_full.wait(lock);
    }

    it->item_buffer[it->write_position] = item;
    it->write_position += 1;

    if (it->write_position == kItemRepositorySize) {
        it->write_position = 0;
    }
    it->repo_not_empty.notify_all();
}

void consume(ItemRepository* it) {
    int data = 0;
    std::unique_lock<std::mutex> lock(it->mtx);
    while (it->write_position == it->read_position) {
        //empty
        std::cout << "Consumer is waiting for items..." << std::endl;
        it->repo_not_empty.wait(lock);
    }
    data = it->item_buffer[it->read_position];
    it->read_position++;
    
    if (it->read_position == kItemRepositorySize) {
        it->read_position = 0;
    }

    it->repo_not_full.notify_all();
    std::cout << "data:" << data << std::endl;
}

void produce_task() {
    for (int i = 0; i < kItemsToProduce; i++) {
        std::cout << "produce item: " << i << std::endl;
        produce(&gItemRepository, i);
    }
}

void consume_task() {
    static int cnt = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        consume(&gItemRepository);
        cnt += 1;
        if (cnt == kItemsToProduce) {
            break;
        }
    }
}

int main(void) {
    std::thread producer(produce_task);
    std::thread consumer(consume_task);
    producer.join();
    consumer.join();
    return 0;
}

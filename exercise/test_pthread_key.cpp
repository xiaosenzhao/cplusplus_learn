#include <stdio.h>
#include <pthread.h>
#include <thread>
#include <chrono>

pthread_key_t key;

void echomsg(int t) {
    printf("destructor excuted in thread %d, param=%d\n", pthread_self(), t);
}

void* child1(void *arg) {
    pthread_t tid = pthread_self();
    printf("thread %d enter\n", tid);
    pthread_setspecific(key, (void *)tid);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    printf("thread %d returns %d and key %d\n", tid, pthread_getspecific(key), key);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return nullptr;
}

void* child2(void *arg) {
    pthread_t tid=pthread_self();
    printf("thread %d enter\n", tid);
    pthread_setspecific(key, (void *)tid);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    printf("thread %d returns %d and key %d\n", tid, pthread_getspecific(key), key);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return nullptr;
}

int main(void) {
    pthread_t tid1, tid2;
    printf("this is main thread\n");
    pthread_key_create(&key, (void (*)(void *))echomsg);
    pthread_create(&tid1, NULL, child1, NULL);
    pthread_create(&tid2, NULL, child2, NULL);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    pthread_key_delete(key);
    printf("main thread exit\n");
    return 0;
}

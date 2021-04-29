#include <sys/time.h>
#include<cstdlib>
#include <stdio.h>

inline void srand_init() {
    timeval ts;
    gettimeofday(&ts, NULL);
    srand((unsigned int)(ts.tv_usec));
}

static const int RAND_BUF_NUM = 1024;  /**<rand_r buffer number*/
class Rander {
public:
    Rander() : _rand_buf_pos(0) {
    }

    inline int init() {
        srand_init();
        for (int i = 0; i < RAND_BUF_NUM; ++i) {
            _rand_buf[i] = rand();
        }
        _rand_buf_pos = 0;
        return 0;
    }

    int produce();
    int produce(int min, int max);
private:
    unsigned int _rand_buf[RAND_BUF_NUM];
    unsigned int _rand_buf_pos;
};

int Rander::produce() {
    int x = rand_r(&_rand_buf[_rand_buf_pos]);
    timeval ts;
    gettimeofday(&ts, NULL);
    _rand_buf[_rand_buf_pos] = x + (unsigned int)ts.tv_usec + rand();
    _rand_buf_pos = (_rand_buf_pos + 1) % RAND_BUF_NUM;
    return x;
}
int Rander::produce(int min, int max) {
    if (min > max){
        min ^= max;
        max ^= min;
        min ^= max; // swap
    }
    double step = (double) (max - min);
    unsigned int x  = rand_r(&_rand_buf[_rand_buf_pos]);
    timeval ts;
    gettimeofday(&ts, NULL);
    _rand_buf[_rand_buf_pos] = x + (unsigned int)ts.tv_usec + rand();
    _rand_buf_pos = (_rand_buf_pos + 1) % RAND_BUF_NUM;
    return min + (int) (step * x / (RAND_MAX + 1.0));
}

int main(void) {
    Rander rander;
    rander.init();
    int ret[100000];

    for (int i = 0; i < 100000; i++) {
        ret[i] = 0;
    }
    for (int i = 0; i < 100000; i++) {
        ret[i] = rander.produce() % 100;
        printf("%d ", ret[i]);
    }
    printf("\n");
    int count = 0;
    for (int i = 0; i < 100000; i++) {
        if (ret[i] < 20) {
            count += 1;
        }
    }
    printf("%d\n", count);
    return 0;
}

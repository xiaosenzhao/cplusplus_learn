/* c struct 末尾定义一个长度为 0 的数组
 * 可以实现变长的数据结构
 * 数据结构后的内存即为该数组内存
 * 由于减少了一次内存寻址，性能有提升
 * 依赖编译器，gnu 支持
*/
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

struct test1 {
	int a;
    int *b;
};

struct test2 {
    int a;
    int b[0];
};

struct test3 {
    int a;
    int b[1];
};

int main(int argc, char** argv) {
    struct test1 *val1;
    struct test2 *val2;
    struct test3 *val3;

    int i = 0;

    printf("the length of struct test1: %lu\n", sizeof(struct test1));
    printf("the length of struct test2: %lu\n", sizeof(struct test2));
    printf("the length of struct test3: %lu\n", sizeof(struct test3));

    val1 = (struct test1*)malloc(sizeof(struct test1));
    val1->a = 1;
    val1->b = (int*)malloc(sizeof(int));
    *val1->b = 1;
    printf("\nval1->a=%d, *(val1->b)=%d\n", val1->a, *val1->b);

    val2 = (struct test2*)malloc(sizeof(struct test2) + sizeof(int) * LENGTH);
    val2->a = 2;
    printf("\nval2->a=%d\n", val2->a);
    for (i = 0; i < LENGTH; i++) {
        val2->b[i] = i;
        printf("val2->b[i]=%d\t", val2->b[i]);
    }
    printf("\n");

    val3 = (struct test3*)malloc(sizeof(struct test3));
    val3->a = 3;
    (val3->b)[0] = 3;
    printf("val3->a=%d, (val3->b)[0]=%d\n", val3->a, (val3->b)[0]);

    free(val1->b);
    free(val1);
    free(val2);
    free(val3);
    return 0;
}
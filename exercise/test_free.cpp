#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char* p = (char*) malloc(sizeof(char) * 10);
    int* i = (int*)p;
    free(i);

    //i = (int*)p + 1;
    //free(i);
    return 0;
}
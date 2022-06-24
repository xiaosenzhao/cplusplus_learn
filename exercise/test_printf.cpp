#include <stdio.h>
int main() {
  int a = 3;
  double b = 5;
  // double类型强转为int输出。double是8个字节，int是4个字节，选择double的低4个字节输出
  printf("%d\n", a + a / 2 + b / 2);
  return 0;
}

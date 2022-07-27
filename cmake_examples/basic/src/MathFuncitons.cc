#include "MathFunctions.h"

double power(double base, int exponent) {
  if (exponent == 0) {
    return 1;
  }

  double result = 1.0;
  for (int i = 1; i <= exponent; ++i) {
    result *= base;
  }
  return result;
}

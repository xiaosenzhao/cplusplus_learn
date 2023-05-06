#include <stdio.h>

#define DOGS \
  { C(JACK_RUSSELL), C(BULL_TERRIER), C(ITALIAN_GREYHOUND) }
#undef C
#define C(a) ENUM_##a
enum dog_enums DOGS;
#undef C
#define C(a) #a
char *dog_strings[] = DOGS;
char *dog_to_string(enum dog_enums dog) { return dog_strings[dog]; }

int main(void) {
  enum dog_enums dog = (enum dog_enums)0;
  char *a = dog_to_string(dog);
  printf("dog: %s\n", a);
  return 0;
}

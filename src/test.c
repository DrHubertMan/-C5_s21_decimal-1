#include "s21_decimal.h"

int main() {
  float a = 12.34;
  float b = 10;
  s21_decimal example1, example2;
  s21_float_to_decimal(a, &example1);
  s21_float_to_decimal(b, &example2);

  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(example1, i));
  }
  printf(" var 1\n_____________________________________________\n");

  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(example2, i));
  }
  printf(" var 2\n_____________________________________________\n");

  printf("%d\n", s21_is_less(example1, example2));

  return 0;
}

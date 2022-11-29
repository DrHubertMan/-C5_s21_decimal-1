#include "s21_decimal.h"

int main() {
  float a = 5;
  float b = 2;
  s21_decimal example1, example2, result;
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

  s21_div(example1, example2, &result);
  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(result, i));
  }
  printf(" result \n_____________________________________________\n");

  return 0;
}

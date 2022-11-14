#include "s21_decimal.h"

int main() {
  int number1 = -10000000;
  int number2 = -100;
  // scanf("%d %d", &number1, &number2);
  s21_decimal example1, example2, result;
  s21_int_to_decimal(number1, &example1);
  s21_int_to_decimal(number2, &example2);
  s21_mod(example1, example2, &result);
  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(example1, i));
  }
  printf("\n");
  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(example2, i));
  }
  printf("\n");
  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(result, i));
  }
  printf("\n");
  return 0;
}

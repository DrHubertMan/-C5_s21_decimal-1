#include "s21_decimal.h"

int main() {
  /*
  int number1 = 78;
  int number2 = 33;
  // scanf("%d %d", &number1, &number2);
  s21_decimal example1, example2, result;
  s21_int_to_decimal(number1, &example1);
  s21_int_to_decimal(number2, &example2);
  
  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(example1, i));
  }
  printf(" var 1\n_____________________________________________\n");
  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(example2, i));
  }
  printf(" var 2\n_____________________________________________\n");

  s21_mod(example1, example2, &result);
  
  for (int i = MAX_DEC_BIT; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(result, i));
  }
  printf("\n");
  */
  float a = -0.02;
  float b = 2;
  int exp_a = s21_get_float_exp(&a);
  int exp_b = s21_get_float_exp(&b);
  s21_decimal example1, example2;
  s21_float_to_decimal(a, &example1);
  s21_float_to_decimal(b, &example2);

  for (int i = 127; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(example1, i));
  }
  printf(" var 1\n_____________________________________________\n");


  for (int i = 127; i >= 0; i--) {
    printf("%d", s21_get_bit_dec(example2, i));
  }
  printf(" var 2\n_____________________________________________\n");

  for (int i = 31; i >= 0; i--) {
    printf("%d", s21_get_bit(exp_a, i));
  }
  printf(" exp_a\n_______________\n");
  for (int i = 31; i >= 0; i--) {
    printf("%d", s21_get_bit(exp_b, i));
  }
  printf(" exp_a\n_______________\n");
  return 0; 
}

#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf1 = value_1;
  s21_decimal buf2 = value_2;

  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

  int sign1 = s21_get_bit_dec(buf1, MAX_DEC_BIT);
  int sign2 = s21_get_bit_dec(buf2, MAX_DEC_BIT);

  if (sign1 && sign2) {
    s21_set_bit_dec(result, 1, MAX_DEC_BIT);
    s21_negate(buf1, &buf1);
    s21_negate(buf2, &buf2);
  } else if (sign1 && !sign2) {
    s21_set_bit_dec(&buf1, 0, MAX_DEC_BIT);
    s21_invert_num(&buf1);
  } else if (sign2 && !sign1) {
    s21_set_bit_dec(&buf2, 0, MAX_DEC_BIT);
    s21_invert_num(&buf2);
  }

  s21_decimal_add(buf1, buf2, result);

  if (sign1 && !sign2) {
    s21_add_diff(&buf1, &buf2, result);
  } else if (!sign1 && sign2) {
    s21_add_diff(&buf2, &buf1, result);
  }
  return exit_flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf2 = value_2;

  s21_negate(buf2, &buf2);
  s21_add(value_1, buf2, result);

  return exit_flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf1 = value_1;
  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

  int sign1 = s21_get_bit_dec(value_1, MAX_DEC_BIT);
  int sign2 = s21_get_bit_dec(value_2, MAX_DEC_BIT);

  int rang = s21_get_position_last_bit(value_2);
  int shift = 0;
  for (int i = 0; i <= rang; i++, shift++) {
    int bit_value_2 = s21_get_bit_dec(value_2, i);
    if (bit_value_2) {
      s21_shift_dec(&buf1, shift);
      s21_add(buf1, *result, result);
    }
  }

  if (sign1 && sign2) {
    s21_set_bit_dec(result, 0, MAX_DEC_BIT);
  } else if (!sign1 && !sign2) {
    s21_set_bit_dec(result, 0, MAX_DEC_BIT);
  } else if ((sign1 && !sign2) || (!sign1 && sign2))
    s21_set_bit_dec(result, 1, MAX_DEC_BIT);
    
  return exit_flag;
}

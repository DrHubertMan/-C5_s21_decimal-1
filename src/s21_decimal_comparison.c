#include "s21_decimal.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int result = 1;
  if (s21_is_two_zero(num1, num2)) {
    result = 1;
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = MAX_INT_BIT; j >= 0; j--) {
        if (s21_get_bit(num1.bits[i], j) != s21_get_bit(num2.bits[i], j)) {
          result = 0;
          break;
        }
      }
    }
  }
  return result;
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return s21_is_equal(num1, num2) ? 0 : 1;
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int result = 0;

  int sign1 = s21_get_bit_dec(num1, MAX_DEC_BIT);
  int sign2 = s21_get_bit_dec(num2, MAX_DEC_BIT);

  int scale1 = s21_get_scale(&num1);
  int scale2 = s21_get_scale(&num2);

  s21_decimal tmp1 = num1;
  s21_decimal tmp2 = num2;

  if (scale1 > scale2) {
    int scale_dif = scale1 - scale2;
    s21_mul_ten(&tmp2, scale_dif);
  } else if (scale2 > scale1) {
    int scale_dif = scale2 - scale1;
    s21_mul_ten(&tmp1, scale_dif);
  }

  if (sign1 > sign2) {
    result = 1;
  } else if (sign1 && sign2) {
    for (int i = 95; i >= 0; i--) {
      if (s21_get_bit_dec(tmp1, i) < s21_get_bit_dec(tmp2, i)) {
        break;
      } else if (s21_get_bit_dec(tmp1, i) > s21_get_bit_dec(tmp2, i)) {
        result = 1;
        break;
      }
    }
  } else if (!sign1 && !sign2) {
    for (int i = 95; i >= 0; i--) {
      if (s21_get_bit_dec(tmp1, i) > s21_get_bit_dec(tmp2, i)) {
        break;
      } else if (s21_get_bit_dec(tmp1, i) < s21_get_bit_dec(tmp2, i)) {
        result = 1;
        break;
      }
    }
  }
  if (s21_is_two_zero(num1, num2))
    result = 0;
  return result;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  return s21_is_less(num2, num1);
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  int result = 0;
  if (s21_is_equal(num1, num2) || s21_is_less(num1, num2))
    result = 1;
  return result;
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  int result = 0;
  if (s21_is_equal(num1, num2) || s21_is_greater(num1, num2))
    result = 1;
  return result;
}
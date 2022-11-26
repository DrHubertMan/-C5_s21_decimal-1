#include "s21_decimal.h"

int s21_get_bit(int src, int num) { return src & (1 << num) ? 1 : 0; }

int s21_get_bit_dec(s21_decimal num, int pos) {
  return num.bits[pos / 32] & (1 << pos % 32) ? 1 : 0;
}

void s21_set_bit(int *num, int bit, int position) {
  (bit == 1) ? (*num |= (1 << position)) : (*num &= ~(1 << position));
}

void s21_set_bit_dec(s21_decimal *num, int bit, int position) {
  (bit == 1) ? (num->bits[position / 32] |= (1 << position % 32))
             : (num->bits[position / 32] &= ~(1 << position % 32));
}

void s21_invert_num(s21_decimal *num) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j <= MAX_INT_BIT; j++) {
      s21_get_bit(num->bits[i], j) ? s21_set_bit(&num->bits[i], 0, j)
                                   : s21_set_bit(&num->bits[i], 1, j);
    }
  }
}

int s21_get_position_last_bit(s21_decimal num) {
  int result = 95;
  for (int i = 95; i >= 0; i--) {
    if (s21_get_bit_dec(num, i)) {
      break;
    }
    result--;
  }
  return result;
}

int s21_decimal_add(s21_decimal buf1, s21_decimal buf2, s21_decimal *result) {
  int exit_flag = 0;
  int mem = 0;
  for (int j = 0; j <= 95; j++) {
    int num1_bit = s21_get_bit_dec(buf1, j);
    int num2_bit = s21_get_bit_dec(buf2, j);
    if (num1_bit && num2_bit) {
      if (!mem) {
        s21_set_bit_dec(result, 0, j);
        mem = 1;
        continue;
      } else if (mem) {
        s21_set_bit_dec(result, 1, j);
        mem = 1;
        continue;
      }
    } else if ((num1_bit && !num2_bit) || (!num1_bit && num2_bit)) {
      if (!mem) {
        s21_set_bit_dec(result, 1, j);
        continue;
      } else if (mem) {
        s21_set_bit_dec(result, 0, j);
        mem = 1;
        continue;
      }
    } else if (!num1_bit && !num2_bit) {
      if (mem) {
        s21_set_bit_dec(result, 1, j);
        mem = 0;
        continue;
      }
    }
  }
  return exit_flag;
}

int s21_add_diff(s21_decimal *buf1, s21_decimal *buf2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal one;
  int one_dec = 1;
  s21_int_to_decimal(one_dec, &one);

  s21_invert_num(buf1);
  int proof =
      s21_is_less(*buf1, *buf2); // proof результат  сравнения "по модулю"
  if (proof) {
    s21_decimal_add(*result, one, result);
  } else if (!proof) {
    s21_invert_num(result);
    s21_set_bit_dec(result, 1, MAX_DEC_BIT);
  }
  return exit_flag;
}

void s21_shift_dec(s21_decimal *num, int shift) {
  s21_decimal buf = *num;
  for (int i = 0; i < 95; i++) {
    int bit = s21_get_bit_dec(buf, i);
    s21_set_bit_dec(num, bit, i + shift);
  }
  for (int j = 0; j < shift; j++) {
    s21_set_bit_dec(num, 0, j);
  }
}

// catch float exp
int s21_get_float_exp(float *src) {
  return ((*(int *)src & ~0x80000000) >> 23) - 127;
}

int s21_get_float_sign(float *src) { return *(int *)src >> 31; }

// catch decimal scale
int s21_get_scale(const s21_decimal *varPtr) {
  return (char)(varPtr->bits[3] >> 16);
}

int s21_is_zero(s21_decimal value) {
  int result = 1;
  for (int i = 0; i < 95; i++) {
    if (s21_get_bit_dec(value, i))
      result = 0;
  }
  return result;
}

int s21_is_two_zero(s21_decimal value1, s21_decimal value2) {
  int result = 0;
  if (s21_is_zero(value1) && s21_is_zero(value2)) {
    result = 1;
  }
  return result;
}

void s21_mul_ten(s21_decimal *num, int count) {
  int sign = s21_get_bit_dec(*num, MAX_DEC_BIT);
  int counter = count;
  num->bits[3] = 0;
  for (int i = 0; i < counter; i++) {
    s21_decimal tmp1 = *num;
    s21_decimal tmp2 = *num;
    s21_shift_dec(&tmp1, 1);
    s21_shift_dec(&tmp2, 3);
    s21_add(tmp1, tmp2, num);
  }
  s21_set_bit_dec(num, sign, MAX_DEC_BIT);
}

void s21_set_scale(s21_decimal *value, int exp) {
  for (int i = 16; i < 24; i++) {
    s21_set_bit(&value->bits[3], s21_get_bit(exp, i - 16), i);
  }
}
// int s21_is_inf(s21_decimal value) {
//   int result = 0;
//   int scale = 1;
//   int sign = s21_get_bit_dec(value, MAX_DEC_BIT);
//   int zero_mantis = s21_is_zero(value);
//   for (int i = 16; i > 24; i++) {
//     printf("%d\n", s21_get_bit(value.bits[3], i));
//     scale = 0;
//   }
//
//   if (scale && zero_mantis && !sign) {
//     result = 1; // +inf
//   } else if (scale && zero_mantis && sign) {
//     result = 2; // -inf
//   }
//   return result;
// }
//
// void s21_set_inf(s21_decimal *value) {
//   value->bits[0] = value->bits[1] = value->bits[2] = value->bits[3] = 0;
// }
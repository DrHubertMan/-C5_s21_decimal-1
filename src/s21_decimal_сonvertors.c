#include "s21_decimal.h"

int s21_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
  if (src < 0) {
    s21_set_bit(&dst->bits[3], 1, MAX_INT_BIT);
    src *= -1;
  }
  dst->bits[0] = src;
  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  *dst = 0;
  int sign_dec = s21_get_bit_dec(src, MAX_DEC_BIT);
  *dst = src.bits[0];
  if (sign_dec)
    *dst *= -1;
  return result;
}

int s21_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;
  int sign = s21_get_float_sign(&src);
  int exp = s21_get_float_exp(&src);
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;

  if (src < 0) {
    s21_set_bit(&dst->bits[3], 1, MAX_INT_BIT);
    src *= -1;
  }
  
  if (dst && src != 0) {
    double temp = (double)fabs(src);
    int off =0;
    for (; off < 28 && (int)temp / (int)pow(2,21) == 0; temp *=10, off++) {
    }
    temp= round(temp);
    if (off <= 28 && (exp > -94 && exp < 96)) {
      floatbits mantis;
      temp = (float) temp;
      for(; fmod(temp,10) == 0 && off > 0; off--, temp /= 10) {
      }
      mantis.fl = temp;
      exp = s21_get_float_exp(&mantis.fl);
      dst->bits[exp / 32] |= 1 << exp % 32;
      for (int i = exp - 1, j = 22; j >= 0; i--, j--)
        if ((mantis.ui & (1 << j)) != 0) dst->bits[i / 32] |= 1 << i % 32;
      dst->bits[3] = (sign << 31) | (off << 16);
    }
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result =0;
  double temp = 0;
  int off =0;
  for (int i=0; i<96;i++) {
    if ((src.bits[i/32] & (1 << i%32)) !=0) {
      temp += pow(2,i);
    }
  }
  if ((off = (src.bits[3] & ~0x80000000) >> 16) > 0) {
      for (int i = off; i > 0; i--) temp /= 10.0;
    }
  *dst = (float)temp;
  *dst *= src.bits[3] >> 31 ? -1 : 1;
  return result;
}

#include"s21_decimal.h"

int s21_int_to_decimal(int src, s21_decimal *dst) {
    int result = 0;
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
    if( src < 0 ) {
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
    if (sign_dec) *dst *= -1;
    return result;
}
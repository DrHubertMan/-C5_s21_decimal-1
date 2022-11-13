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
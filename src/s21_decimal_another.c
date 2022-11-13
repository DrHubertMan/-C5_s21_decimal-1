#include"s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    int exit_flag = 0;
    result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
    *result = value;
    int sign_value = s21_get_bit_dec(value, MAX_DEC_BIT);
    if (sign_value) {
        s21_set_bit(&result->bits[3], 0, MAX_INT_BIT);
    } else {
        s21_set_bit(&result->bits[3], 1, MAX_INT_BIT);
    }
    return exit_flag;
}
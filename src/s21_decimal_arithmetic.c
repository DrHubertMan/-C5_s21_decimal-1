#include"s21_decimal.h"

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
    int exit_flag = 0;

    s21_decimal buf1 = num1;
    s21_decimal buf2 = num2;
    
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
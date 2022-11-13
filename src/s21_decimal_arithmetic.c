#include"s21_decimal.h"

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
    int exit_flag = 0;

    s21_decimal buf1 = num1;
    s21_decimal buf2 = num2;
    
    s21_decimal one;
    int one_dec = 1;
    s21_int_to_decimal(one_dec, &one);

    result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

    int sign1 = s21_get_bit_dec(buf1, MAX_DEC_BIT);
    int sign2 = s21_get_bit_dec(buf2, MAX_DEC_BIT);
    
    if (sign1 && sign2) {
        s21_set_bit(&result->bits[3], 1, MAX_INT_BIT);
        s21_set_bit(&buf1.bits[3], 0, MAX_INT_BIT);
        s21_set_bit(&buf2.bits[3], 0, MAX_INT_BIT);
    } else if (sign1 && !sign2) {
        s21_set_bit(&buf1.bits[3], 0, MAX_INT_BIT);
        s21_invert_num(&buf1);
    } else if (sign2 && !sign1) {
        s21_set_bit(&buf2.bits[3], 0, MAX_INT_BIT);
        s21_invert_num(&buf2);
    }

    int mem = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= MAX_INT_BIT; j++) {
            int num1_bit = s21_get_bit(buf1.bits[i], j);
            int num2_bit = s21_get_bit(buf2.bits[i], j);
            if (num1_bit == 1 && num2_bit == 1) {
                if (mem == 0) {
                    s21_set_bit(&result->bits[i], 0, j);
                    mem = 1;
                } else {
                    s21_set_bit(&result->bits[i], 1, j);
                    mem = 1;
                }
            } else if ((num1_bit == 0 && num2_bit == 1) || (num1_bit == 1 && num2_bit == 0)) {
                if (mem == 0) {
                    s21_set_bit(&result->bits[i], 1, j);
                } else {
                    s21_set_bit(&result->bits[i], 0, j);
                    mem = 0;
                }
            } else if (num1_bit == 0 && num2_bit == 0 ) {
                if (mem == 1) {
                    s21_set_bit(&result->bits[i], 1, j);
                    mem = 0;
                }
            }
        }
    }

    
    //if (sign1 && !sign2) {
    //    s21_invert_num(&buf1);
    //    int proof = s21_is_less(buf1, buf2); // proof результат  сравнения "по модулю"
    //    if (proof) {
    //        s21_add(*result, one, result);
    //    } else if (!proof) {
    //        s21_invert_num(result);
    //        s21_set_bit(&result->bits[3], 1, MAX_INT_BIT);
    //    }
    //}

    return exit_flag;
}

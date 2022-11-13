#include"s21_decimal.h"

int s21_get_bit(int src, int num) {
    return src & (1<<num) ? 1 : 0;
}       

int s21_get_bit_dec(s21_decimal num, int pos) {
    return num.bits[pos/32] & (1<< pos % 32) ? 1 : 0;
}

void s21_set_bit(int *num, int bit, int position) {
    (bit == 1) ? (*num |= (1 << position)) : (*num &= ~( 1 << position ));
}

void s21_set_bit_dec(s21_decimal *num, int bit, int position) {
    (bit == 1) ? (num->bits[position/32] |= (1 << position % 32)) 
                : (num->bits[position/32] &= ~( 1 << position % 32));
}

void s21_invert_num(s21_decimal *num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= MAX_INT_BIT; j++) {
            s21_get_bit(num->bits[i], j) ? s21_set_bit(&num->bits[i], 0, j) : s21_set_bit(&num->bits[i], 1, j);
        }
    }
}

int s21_get_position_last_bit(s21_decimal num) {
    int result = 63;
    for (int i = 63; i >= 0; i--) {
        if(s21_get_bit_dec(num, i)) {
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
    int proof = s21_is_less(*buf1, *buf2); // proof результат  сравнения "по модулю"
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
    for (int i = 0; i < 95; i++){
        int bit = s21_get_bit_dec(buf, i);
        s21_set_bit_dec(num, bit, i+shift);
    }
    for (int j = 0; j <= shift; j++) {
        s21_set_bit_dec(num, 0, j);
    }
}
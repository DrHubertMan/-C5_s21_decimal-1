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

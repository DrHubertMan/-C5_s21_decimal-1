#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INT_BIT 31
#define MAX_DEC_BIT 127

typedef struct {
    int bits[4];
} s21_decimal;

// вспомогательные

int s21_get_bit(int src, int num); // узнаем конкретный бит по позиции
int s21_get_bit_dec(s21_decimal num, int pos); // узнаем конкретный бит по позиции во всем децимале
void s21_int_to_bit_str(int number, char *str); // перевод инта в двоичный формат и запись в строку
void s21_set_bit(int *num, int bit, int position); // вкл/выкл бита в конкретной позиции
void s21_invert_num(s21_decimal *num); // инвертировать число 
int s21_get_position_last_bit(s21_decimal num); // узнать последний включенный бит в числе

// сравнение

int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);

// арифметика

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal *result);

// преобразователи

int s21_int_to_decimal(int src, s21_decimal *dst); 

int main() {
    int number1 = 3;
    int number2 = 5;
    // char str[33] = {};
    s21_decimal example1, example2, result;
    s21_int_to_decimal(number1, &example1);
    s21_int_to_decimal(number2, &example2);
    s21_add(example1, example2, &result);
    for (int i = MAX_DEC_BIT; i >= 0; i--) {
        printf("%d", s21_get_bit_dec(example1, i));
    }
    printf("\n");
    for (int i = MAX_DEC_BIT; i >= 0; i--) {
        printf("%d", s21_get_bit_dec(example2, i));
    }
    printf("\n");
    for (int i = MAX_DEC_BIT; i >= 0; i--) {
        printf("%d", s21_get_bit_dec(result, i));
    }
    printf("\n");
    return 0;
}

// find out the bit

int s21_get_bit(int src, int num) {
    return src & (1<<num) ? 1 : 0;
}       

int s21_get_bit_dec(s21_decimal num, int pos) {
    return num.bits[pos/32] & (1<< pos % 32) ? 1 : 0;
}

void s21_int_to_bit_str(int number, char *str) {
    for (int i = MAX_INT_BIT, j = 0; i >= 0; i--, j++) {
        char bit = s21_get_bit(number, i) + 48;
        str[j] = bit;
    }
}

// set the bit

void s21_set_bit(int *num, int bit, int position) {
    (bit == 1) ? (*num |= (1 << position)) : (*num &= ~( 1 << position ));
}

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

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
    int result = 1;
    for ( int i = 0; i < 4; i++ ) {
        for (int j = MAX_INT_BIT; j >= 0; j--) {
            if (s21_get_bit(num1.bits[i],j) != s21_get_bit(num2.bits[i], j)) {
                result = 0;
                break;
            }
        }
    }
    return result;
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
    return s21_is_equal(num1, num2) ? 0 : 1;
}

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


void s21_invert_num(s21_decimal *num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= MAX_INT_BIT; j++) {
            s21_get_bit(num->bits[i], j) ? s21_set_bit(&num->bits[i], 0, j) : s21_set_bit(&num->bits[i], 1, j);
        }
    }
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
    int result = 0;
    int sign1 = s21_get_bit_dec(num1, MAX_DEC_BIT);
    int sign2 = s21_get_bit_dec(num2, MAX_DEC_BIT);
    if (sign1 > sign2) {
        result = 1;
    } else if (sign1 && sign2) {
        for (int i = 63; i >= 0; i--) {
            if (s21_get_bit_dec(num1, i) < s21_get_bit_dec(num2, i)) {
                break;
            } else if (s21_get_bit_dec(num1, i) > s21_get_bit_dec(num2, i)) {
                result = 1;
                break;
            }
        }
    } else if (!sign1 && !sign2) {
        for (int i = 63; i >= 0; i--) {
            if (s21_get_bit_dec(num1, i) > s21_get_bit_dec(num2, i)) {
                break;
            } else if (s21_get_bit_dec(num1, i) < s21_get_bit_dec(num2, i)) {
                result = 1;
                break;
            }
        }
    }
    return result;
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
    int result = 0;
    if (s21_is_equal(num1, num2) || s21_is_less(num1, num2)) result = 1;
    return result;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2){
    return s21_is_less(num2, num1);
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
    int result = 0;
    if (s21_is_equal(num1, num2) || s21_is_greater(num1, num2)) result = 1;
    return result;
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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INT_BIT 31

typedef struct {
    int bits[4];
} s21_decimal;

// вспомогательные

int s21_get_bit(s21_decmial num); // узнаем конкретный бит по позиции
void s21_int_to_bit_str(int number, char *str); // перевод инта в двоичный формат и запись в строку
void s21_set_bit(int *num, int bit, int position); // вкл/выкл бита в конкретной позиции
void s21_invert_num(s21_decimal *num); // инвертировать число 
int s21_get_position_last_bit(s21_decimal num); // узнать последний включенный бит в числе

// сравнение

int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);

// арифметика

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal *result);

// преобразователи

void s21_int_to_decimal(int src, s21_decimal *dst); 

int main() {
    int number1 = 2;
    int number2 = 3;
    // char str[33] = {};
    s21_decimal example1, example2;
    s21_int_to_decimal(number1, &example1);
    s21_int_to_decimal(number2, &example2);
    printf("%d\n", s21_get_position_last_bit(example1));
    printf("%d\n", s21_get_position_last_bit(example2));
    printf("%d\n", s21_is_less(example1, example2));
    return 0;
}

// find out the bit

int s21_get_bit(s21_decimal num) {
    for ()
    return src & (1<<num) ? 1 : 0;
}       
дщдщдщдщд

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

void s21_int_to_decimal(int src, s21_decimal *dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
    if( src < 0 ) {
        s21_set_bit(&dst->bits[3], 1, MAX_INT_BIT);
        src *= -1;
    }
    dst->bits[0] = src;
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
    int mem = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= MAX_INT_BIT; j++) {
            int num1_bit = s21_get_bit(num1.bits[i], j);
            int num2_bit = s21_get_bit(num2.bits[i], j);
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
                if (i != 3) {
                    if (mem == 1) {
                        s21_set_bit(&result->bits[i], 1, j);
                        mem = 0;
                    }
                }
            }
        }
    }
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
    int sign1 = s21_get_bit(num1.bits[3], MAX_INT_BIT);
    int sign2 = s21_get_bit(num2.bits[3], MAX_INT_BIT);
    int max1 = s21_get_position_last_bit(num1);
    int max2 = s21_get_position_last_bit(num2);
    if (sign1 > sign2) {
        result += 1;
    } else if (sign1 && sign2) {
        if (max1 > max2) result += 1;
    } else if (!sign1 && !sign2) {
        if (max1 < max2) result += 1;
    }
    return result;
}

int s21_get_position_last_bit(s21_decimal num) {
    int result = 95;
    int helper = 0;
    for (int i = 2; i >= 0; i--) {
        if (helper) break;
        for (int j = MAX_INT_BIT; j >=0; j--) {
            if (s21_get_bit(num.bits[i], j)) {
                helper += 1;
                break;
            }
            result--;
        }
    }
    return result;
}

// не закончена
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
    int result = 0;
    if (s21_is_equal(num1, num2)) result = 1;
    return result;
}

011 3
010 2
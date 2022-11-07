#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INT_BIT 31

typedef struct {
    int bits[4];
} s21_decimal;


int s21_get_bit(int src, int num);
void s21_int_to_bit_str(int number, char *str);
void s21_set_bit(int *num, int bit, int position);
void s21_int_to_decimal(int src, s21_decimal *dst);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal *result);

int main() {
    int number1 = -1;
    int number2 = 12;
    char str[33] = {};
    s21_decimal example1;
    s21_decimal example2;
    s21_decimal result;
    s21_int_to_decimal(number1, &example1);
    s21_int_to_decimal(number2, &example2);
    s21_add(example1, example2, &result);
    s21_int_to_bit_str(result.bits[0], str);
    if (s21_get_bit(result.bits[3], MAX_INT_BIT)) printf("-");
    printf("%d\n%d\n", result.bits[0], s21_get_bit(result.bits[3], MAX_INT_BIT));
    return 0;
}

int s21_get_bit(int src, int num) {
    return src & (1<<num) ? 1 : 0;
}       

void s21_int_to_bit_str(int number, char *str) {
    for (int i = 31, j = 0; i >= 0; i--, j++) {
        char bit = s21_get_bit(number, i) + 48;
        str[j] = bit;
    }
}

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
        if  (result == 0) break;
        for (int j = 31; j >= 0; j--) {
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


// не закончена
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
    int result = 0;
    if (s21_is_equal(num1, num2)) result = 1;
    if (s21_get_bit(num1.bits[3], MAX_INT_BIT) > s21_get_bit(num2.bits[3], MAX_INT_BIT)) result = 1;
    return result;
}

// integer positive negativ not work

int s21_add(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
    int exit_flag = 0;
    int mem = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 32; j++) {
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
            if (i == 3 && j == 31) {
                if (num1_bit == 1 && num2_bit == 1) s21_set_bit(&result->bits[i], 1, j);
            }
        }
    }
    return exit_flag;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STR_SIZE 33

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

int main() {
    int number1 = -12;
    int number2 = 12;
    s21_decimal example1;
    s21_decimal example2;
    s21_int_to_decimal(number1, &example1);
    s21_int_to_decimal(number2, &example2);
    printf("example1 = -%d\nexample2 = %d\n", example1.bits[0], example2.bits[0]);
    int result = s21_is_equal(example1, example2);
    printf("is equal - %d\n", result);
    int result2 = s21_is_not_equal(example1, example2);
    printf("is not equal - %d\n", result2);
    int result3 = s21_is_less_or_equal(example1, example2);
    printf("example1 <= example2 - %d\n", result3);
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
        s21_set_bit(&dst->bits[3], 1, 31);
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

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
    int result = 0;
    if (s21_is_equal(num1, num2)) result = 1;
    if (s21_get_bit(num1.bits[3], 31) > s21_get_bit(num2.bits[3], 31)) result = 1;
    return result;
}

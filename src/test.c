#include"s21_decimal.h"

int main() {
    int number1 = 2147483647;
    int number2 = 2147483647;
    // scanf("%d %d", &number1, &number2);
    s21_decimal example1, example2, result, result1;
    s21_int_to_decimal(number1, &example1);
    s21_int_to_decimal(number2, &example2);
    s21_add(example1, example2, &result);
    s21_add(result, result, &result1);
    for (int i = MAX_DEC_BIT; i >= 0; i--) {
        printf("%d", s21_get_bit_dec(result, i));
    }
    printf("\n");
    for (int i = MAX_DEC_BIT; i >= 0; i--) {
        printf("%d", s21_get_bit_dec(result, i));
    }
    printf("\n");
    for (int i = MAX_DEC_BIT; i >= 0; i--) {
        printf("%d", s21_get_bit_dec(result1, i));
    }
    printf("\n");
    return 0;
}

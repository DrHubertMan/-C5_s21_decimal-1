#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_INT_BIT 31
#define MAX_DEC_BIT 127

typedef struct {
  int bits[4];
} s21_decimal;

// вспомогательные
//_________________________________________________________________________________________________
int s21_get_bit(int src, int num); // узнаем конкретный бит по позиции
int s21_get_bit_dec(
    s21_decimal num,
    int pos); // узнаем конкретный бит по позиции во всем децимале
void s21_set_bit(int *num, int bit,
                 int position); // вкл/выкл бита в конкретной позиции
void s21_set_bit_dec(s21_decimal *num, int bit, int position);
void s21_invert_num(s21_decimal *num); // инвертировать число
int s21_get_position_last_bit(
    s21_decimal num); // узнать последний включенный бит в числе
int s21_decimal_add(s21_decimal buf1, s21_decimal buf2,
                    s21_decimal *result); // для сложения
int s21_add_diff(s21_decimal *buf1, s21_decimal *buf2,
                 s21_decimal *result);           // ciganskye fokusi
void s21_shift_dec(s21_decimal *num, int shift); // сдвиг битов влево
//________________________________________________________________________________________________

// сравнение
//________________________________________________________________________________________________
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
//________________________________________________________________________________________________

// арифметика
//________________________________________________________________________________________________
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//________________________________________________________________________________________________

// преобразователи
//________________________________________________________________________________________________
int s21_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
//________________________________________________________________________________________________

// Another functions
//________________________________________________________________________________________________
int s21_negate(s21_decimal value, s21_decimal *result);
//________________________________________________________________________________________________
#endif // SRC_S21_DECIMAL_H_

#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INT_BIT 31
#define MAX_DEC_BIT 127

/*
  return 1 if NaN and 0 if not
*/
#define S21_IS_NAN(x) __builtin_isnan(x) // this (!(x >= 0) && !(x < 0))
/*
  return 1 if inf and -1 if -inf and 0 if finite
*/
#define S21_IS_INF(x) __builtin_isinf(x) // ((x == S21_INF) || (x == -S21_INF))

typedef struct {
  int bits[4];
} s21_decimal;

// struct for float bits value

typedef union {
  int ui;
  float fl;
} floatbits;

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
int s21_get_float_exp(float *src);
int s21_get_float_sign(float *src);
int s21_get_scale(const s21_decimal *varPtr);
int s21_is_zero(s21_decimal value);
// int s21_is_inf(s21_decimal value);
// void s21_set_inf(s21_decimal *value);
int s21_is_two_zero(s21_decimal value1, s21_decimal value2);
void s21_mul_ten(s21_decimal *num);
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
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//________________________________________________________________________________________________

// арифметика преобразования
//________________________________________________________________________________________________
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
//________________________________________________________________________________________________

// преобразователи
//________________________________________________________________________________________________
int s21_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
//________________________________________________________________________________________________

#endif // SRC_S21_DECIMAL_H_

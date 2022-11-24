#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf1 = value_1;
  s21_decimal buf2 = value_2;
  // int scale1 = s21_get_scale(&buf1);
  // int scale2 = s21_get_scale(&buf2);
  // int scale_result = 0;
  // int scale_differ;
  // 
  // if (scale1 > scale2) {
  //   scale_result = scale1;
  //   scale_differ = scale1 - scale2;
  //   
  // }

  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

  int sign1 = s21_get_bit_dec(buf1, MAX_DEC_BIT);
  int sign2 = s21_get_bit_dec(buf2, MAX_DEC_BIT);

  if (sign1 && sign2) {
    s21_set_bit_dec(result, 1, MAX_DEC_BIT);
    s21_negate(buf1, &buf1);
  } else if (sign1 && !sign2) {
    s21_set_bit_dec(&buf1, 0, MAX_DEC_BIT);
    s21_invert_num(&buf1);
  } else if (sign2 && !sign1) {
    s21_set_bit_dec(&buf2, 0, MAX_DEC_BIT);
    s21_invert_num(&buf2);
  }

  s21_decimal_add(buf1, buf2, result);

  if (sign1 && !sign2) {
    s21_add_diff(&buf1, &buf2, result);
  } else if (!sign1 && sign2) {
    s21_add_diff(&buf2, &buf1, result);
  }
  return exit_flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf2 = value_2;

  s21_negate(buf2, &buf2);
  s21_add(value_1, buf2, result);
  return exit_flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf1 = value_1;

  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

  int sign1 = s21_get_bit_dec(value_1, MAX_DEC_BIT);
  int sign2 = s21_get_bit_dec(value_2, MAX_DEC_BIT);

  if (s21_is_greater(value_2,
                     value_1)) { // если второе значение больше первого, меняем
                                 // местами и перевызываем функцию
    s21_mul(value_2, value_1, result);
  } else {

    int rang = s21_get_position_last_bit(
        value_2); // узнаем позицию последнего значащего бита

    for (int i = 0; i <= rang; i++) {
      int bit_value_2 = s21_get_bit_dec(value_2, i);
      if (bit_value_2) {
        s21_add(buf1, *result, result);
      }
      s21_shift_dec(&buf1, 1);
    }

    if (sign1 == sign2) {
      s21_set_bit_dec(result, 0, MAX_DEC_BIT);
    } else if (sign1 != sign2) {
      s21_set_bit_dec(result, 1, MAX_DEC_BIT);
    }
  }

  return exit_flag;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf1 = value_1; // создаем копию делимого
  s21_decimal buf2 = value_2; // копия делителя
  s21_decimal tmp2 =
      buf2; // вторая копия для проверки условия сдвига, ниже будет понятнее
  s21_decimal zero; // нужен децимал равный нулю для сравнения

  zero.bits[0] = zero.bits[1] = zero.bits[2] = zero.bits[3] =
      0; // зануляем те перееменные у которых нет значения дабы избавиться от
         // мусора
  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

  // получаем знаки делимого и делителя, чтобы определить знак частного
  int sign1 = s21_get_bit_dec(buf1, MAX_DEC_BIT);
  int sign2 = s21_get_bit_dec(buf2, MAX_DEC_BIT);

  // объявляем переменную отвечающую за сдвиг
  int shift = 0;

  // исходя из полученных знаков избавляемся от минусов в тех переменных, в
  // которых они есть
  if (sign1 && sign2) {
    s21_negate(buf1, &buf1);
    s21_negate(buf2, &buf2);
  } else if (sign1 && !sign2) {
    s21_negate(buf1, &buf1);
  } else if (!sign1 && sign2) {
    s21_negate(buf2, &buf2);
  }

  if (s21_is_less(buf1,
                  buf2)) { // тк деление без остатка частное будет равно нулю
    *result = zero;
  } else { // делим
    while (s21_is_greater(buf1, zero) ||
           s21_is_zero(buf1)) { // пока делитель больше нуля
      s21_shift_dec(&tmp2, 1);
      if (s21_is_greater_or_equal(buf1, tmp2)) {
        buf2 = tmp2;
        shift++;
      } else {
        s21_sub(buf1, buf2, &buf1);
        if (s21_is_greater_or_equal(buf1, zero) || s21_is_zero(buf1)) {
          s21_set_bit_dec(result, 1, shift);
        }
        buf2 = value_2;
        tmp2 = buf2;
        shift = 0;
      }
    }
  }
  /*
  далее если знаки одинаковые, то в результате устанавливаем знак +
  если знаки разные, то -
  */
  if (sign1 == sign2) {
    s21_set_bit_dec(result, 0, MAX_DEC_BIT);
  } else if (sign1 != sign2) {
    s21_set_bit_dec(result, 1, MAX_DEC_BIT);
  }

  return exit_flag;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

  s21_div(value_1, value_2, result);
  s21_mul(value_2, *result, result);
  s21_sub(value_1, *result, result);

  return exit_flag;
}

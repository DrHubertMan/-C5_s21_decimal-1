#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  /*
  создаем переменные - копии наших значений
  */
  s21_decimal buf1 = value_1;
  s21_decimal buf2 = value_2;

  /*
  зануляем результат, чтобы не было мусора
  */
  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

  /*
  получаем знаки наших переменных
  */
  int sign1 = s21_get_bit_dec(buf1, MAX_DEC_BIT);
  int sign2 = s21_get_bit_dec(buf2, MAX_DEC_BIT);

  if (sign1 && sign2) { // если оба знака отрицательные
    s21_set_bit_dec(result, 1,
                    MAX_DEC_BIT); // устанавливаем в результате знак минус
    s21_negate(buf1, &buf1); // умножаем переменную на -1
    s21_negate(buf2, &buf2); // умножаем переменную на -1
  } else if (sign1 && !sign2) { // если первое слогаемое отриц
    s21_set_bit_dec(&buf1, 0, MAX_DEC_BIT); // меняем знак на +
    s21_invert_num(
        &buf1); // инвертируем число, для сложения разнознаковых слогаемых
  } else if (sign2 && !sign1) { // если второе слогаемое отриц
    s21_set_bit_dec(&buf2, 0, MAX_DEC_BIT); // меняем знак на +
    s21_invert_num(
        &buf2); // инвертируем число, для сложения разнознаковых слогаемых
  }

  s21_decimal_add(buf1, buf2, result); // складываем

  if (sign1 && !sign2) { // если первое отриц
    s21_add_diff(&buf1, &buf2,
                 result); // вызываем доп функцию, важна очередность слогаемых
  } else if (!sign1 && sign2) { // если второе отриц
    s21_add_diff(&buf2, &buf1,
                 result); // вызываем доп функцию, важна очередность слогаемых
  }
  return exit_flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf2 = value_2;

  s21_negate(buf2, &buf2); // умножаем на -1 второе знач
  s21_add(value_1, buf2, result); // складываем по правилам сложения

  return exit_flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit_flag = 0;

  s21_decimal buf1 = value_1;

  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;

  int sign1 = s21_get_bit_dec(value_1, MAX_DEC_BIT);
  int sign2 = s21_get_bit_dec(value_2, MAX_DEC_BIT);

  if (s21_is_greater(value_2, value_1)) {
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
  } else {                               // делим
    while (s21_is_greater(buf1, zero)) { // пока делитель больше нуля
      /*
      ВАЖНО понимать разницу между tmp2 и buf2 в каждой итерации!!!
      ниже сдвигаю переменную равную делителю на 1 влево,
      чтобы проверить не будет ли она больше делителя после сдвига, если
      делимое все еще больше, сдвигаю фактический делитель и записываю значние
      сдвига
      */
      s21_shift_dec(&tmp2, 1);
      if (s21_is_greater_or_equal(buf1, tmp2) && s21_is_greater(tmp2, zero)) {
        s21_shift_dec(&buf2, 1);
        shift++;
        /*
        если наша tmp2 стала больше делителя, то мы берем значение buf2
        которое сдвигали последний раз в прошлой итерации
        */
      } else {
        s21_set_bit_dec(result, 1, shift); // в результате включаем бит на
                                           // позиции равной величине сдвига
        s21_sub(buf1, buf2, &buf1); // из делимого вычитаем buf2
        buf2 = value_2; // возвращаем исходное значение делителя
        tmp2 = buf2; // аналогично нашей проверочной переменной
        shift = 0; // зануляем сдвиг
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

int s21_mod()
#include "s21_decimal_core.h"
#include "s21_decimal.h"

int s21_negate(s21_decimal decim, s21_decimal *result_decimal) {
  s21_nullify_all_decimal(result_decimal);
  s21_chang_sign(&decim);
  *result_decimal = decim;
  return 0;
}

int s21_truncate(s21_decimal decim, s21_decimal *result_decimal) {
  return s21_truncate_to_scale(decim, 0, result_decimal);
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal one, zeroDotFive, mod_res;

  s21_from_int_to_decimal(1, &one);
  s21_from_int_to_decimal(5, &zeroDotFive);
  s21_set_scale(&zeroDotFive, 1);

  s21_mod(value, one, &mod_res);
  s21_set_sign(&mod_res, 0);
  s21_set_sign(&one, s21_check_sign(value));

  s21_truncate(value, result);
  if (s21_is_greater_or_equal(mod_res, zeroDotFive))
    s21_add(*result, one, result);
  return OK;
}

// floor function
int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one, mod_res;
  s21_from_int_to_decimal(1, &one);

  s21_mod(value, one, &mod_res);
  s21_truncate(value, result);
  if (s21_check_sign(value) == 1 && !s21_is_null_decimal(value) &&
      !s21_is_null_decimal(mod_res)) {
    s21_add_lite(*result, one, result);
    s21_chang_sign(result);
  }
  return OK;
}

// decimal inf value
s21_decimal s21_decimal_get_inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};

  return result;
}

// strtol take string value and convert it into li
int s21_get_float_exp_from_string(char *str) {
  int result = 0;
  char *ptr = str;
  while (*ptr) {
    if (*ptr == 'E') {
      ++ptr;
      result = strtol(ptr, NULL, 10);
      break;
    }
    ++ptr;
  }

  return result;
}

s21_decimal s21_float_string_to_decimal(char *str) {
  int digits_counter = 7;
  s21_decimal result;
  s21_nullify_all_decimal(&result);
  char *ptr = str;
  // get new scale float, because they can be change by s21_from_float_to_dec
  int exp = s21_get_float_exp_from_string(str);

  while (*ptr) {
    if (*ptr == '.') {
      // ignoring point . final scale will b later
      ++ptr;
      continue;
    } else if (*ptr >= '0' && *ptr <= '9') {
      // conver num in string in dec , start with first, by decimal arifmetic
      s21_decimal tmp;
      s21_nullify_all_decimal(&tmp);
      s21_mul(s21_decimal_get_from_char(*ptr),
              s21_int128_get_ten_pow(digits_counter), &tmp);
      s21_add(result, tmp, &result);
      --digits_counter;
      ++ptr;
    } else {
      break;
    }
  }
  // remamber that scale have shift, now take right scale in decimal
  exp = exp - 7;

  if (exp > 0) {
    // for positive scale take mul 10^exp
    s21_mul(result, s21_int128_get_ten_pow(exp), &result);
  } else if (exp < 0) {
    // for negative scale take div 10^exp
    if (exp < -28) {
      // the last if() for smallest scale (as 10^28 example) we cant
      // make div much than this scale
      s21_div(result, s21_int128_get_ten_pow(28), &result);
      exp += 28;
    }
    s21_div(result, s21_int128_get_ten_pow(-exp), &result);
  }

  return result;
}

// for s21_float_string_to_decimal
s21_decimal s21_decimal_get_from_char(char c) {
  s21_decimal result;

  switch (c) {
    case '0':
      s21_nullify_all_decimal(&result);
      break;
    case '1':
      result = s21_decimal_get_one();
      break;
    case '2':
      s21_from_int_to_decimal(2, &result);
      break;
    case '3':
      s21_from_int_to_decimal(3, &result);
      break;
    case '4':
      s21_from_int_to_decimal(4, &result);
      break;
    case '5':
      s21_from_int_to_decimal(5, &result);
      break;
    case '6':
      s21_from_int_to_decimal(6, &result);
      break;
    case '7':
      s21_from_int_to_decimal(7, &result);
      break;
    case '8':
      s21_from_int_to_decimal(8, &result);
      break;
    case '9':
      s21_from_int_to_decimal(9, &result);
      break;
  }

  return result;
}

// if we needed 1 num
s21_decimal s21_decimal_get_one(void) {
  s21_decimal result;
  s21_nullify_all_decimal(&result);
  result.bits[0] = 1;

  return result;
}

// return 10 ^ pow like int128
// correct value from 0 to 38
s21_decimal s21_int128_get_ten_pow(int pow) { 
    return all_ten_pows[pow]; 
}
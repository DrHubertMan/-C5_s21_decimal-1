#include "decimal_core.h"
#include "s21_decimal.h"

int s21_shift(s21_decimal *src, int n)
{
    // Mult number by 10 shift by the number to te left
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal tmp_result;
    s21_nullify_all_decimal(&tmp_result);

    int exp = s21_get_scale(*src);
    int status = exp == 28;

    while (!status && n--)
    {
        status = s21_mul_lite(*src, ten, &tmp_result);
        if (!status)
        {
            *src = tmp_result;
            s21_nullify_all_decimal(&tmp_result);
            status = (++exp == 28);
        }
    }

    s21_set_scale(src, exp);
    return status;
}

int s21_balancing(s21_decimal *src1, s21_decimal *src2)
{
    int difference = s21_get_scale(*src1) - s21_get_scale(*src2);

    if (diff)
    {
        if (diff > 0)
            s21_shifting(b, diff);
        else
            s21_shifting(a, -diff);

        difference = get_exp(*a) - get_exp(*b);
        if (diff)
        {
            if (diff > 0)
                s21_bank_round(a, diff);
            else
                s21_bank_round(b, -diff);
        }
    }

    return OK;
}

int s21_bank_rounding(int num) {
  /// returns 1 if you need to apply bank rounding or 0 if not
  return (num % 10 >= 5 || (num % 10 == 5 && (num / 10) % 2));
}

int s21_bank_round(s21_decimal *src1, int num) {
  s21_decimal one, ten, hund;
  s21_from_int_to_decimal(1, &one);
  s21_from_int_to_decimal(10, &ten);
  s21_from_int_to_decimal(100, &hund);

  while (num--) {
    s21_decimal mod_res;
    s21_nullify_all_decimal(&mod_res);
    s21_mod_sign(*src1, hund, &mod_res);

    int exp = s21_get_scale(*src1) - 1;
    s21_int_div(*src1, ten, src1);
    s21_set_scale(src1, exp);

    if (s21_bank_rounding(mod_res.bits[0])) {
      int buffer = number->bits[INFO_BIT];
      s21_add_lite(*src1, one, src1);
      number->bits[INFO_BIT] = buffer;
    }
  }

  return OK;
}
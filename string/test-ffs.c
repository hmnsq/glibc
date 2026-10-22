/* Copyright (C) 1994-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#شامل <stdlib.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <support/check.h>

خالی try (ثابت حرف *name, طویل طویل صحیح param, صحیح قدر, صحیح expected)
{
  اگر (قدر != expected)
    {
      لکھو ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, قدر);
      support_ریکارڈ_failure ();
    }
  ورنہ
    لکھو ("%s(%#llx) as expected %d\n", name, param, قدر);
}

صحیح
do_test (خالی)
{
  صحیح i;

#تعریف_کرو TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  برائے (i=0 ; i < 8 * حجم (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  برائے (i=0 ; i < 8 * حجم (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, صحیح);
  TEST (ffsl, طویل صحیح);
  TEST (ffsll, طویل طویل صحیح);

  واپس 0;
}

#شامل <support/test-driver.c>

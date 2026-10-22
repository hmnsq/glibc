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

#ضمن <stdlib.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <support/check.h>

فراغ try (ثابت حرف *name, long long صحيح param, صحيح قيمة, صحيح expected)
{
  إذا (قيمة != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, قيمة);
      support_record_failure ();
    }
  وإلا
    printf ("%s(%#llx) as expected %d\n", name, param, قيمة);
}

صحيح
do_test (فراغ)
{
  صحيح i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  لكل (i=0 ; i < 8 * حجم (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  لكل (i=0 ; i < 8 * حجم (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, صحيح);
  TEST (ffsl, long صحيح);
  TEST (ffsll, long long صحيح);

  إرجاع 0;
}

#ضمن <support/test-driver.c>

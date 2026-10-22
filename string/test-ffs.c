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

#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <support/check.h>

শূন্য try (ধ্রুবক অক্ষর *name, long long পূর্ণসংখ্যা param, পূর্ণসংখ্যা মান, পূর্ণসংখ্যা expected)
{
  যদি (মান != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, মান);
      support_record_failure ();
    }
  অন্যথা
    printf ("%s(%#llx) as expected %d\n", name, param, মান);
}

পূর্ণসংখ্যা
do_test (শূন্য)
{
  পূর্ণসংখ্যা i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  জন্য (i=0 ; i < 8 * আকার (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  জন্য (i=0 ; i < 8 * আকার (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, পূর্ণসংখ্যা);
  TEST (ffsl, long পূর্ণসংখ্যা);
  TEST (ffsll, long long পূর্ণসংখ্যা);

  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>

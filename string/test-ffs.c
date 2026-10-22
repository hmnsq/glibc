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

শূন্য try (ধ্রুব বর্ণ *name, long long পূর্ণাঙ্ক param, পূর্ণাঙ্ক মান, পূর্ণাঙ্ক expected)
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

পূর্ণাঙ্ক
do_test (শূন্য)
{
  পূর্ণাঙ্ক i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  প্রতি (i=0 ; i < 8 * পরিমাণ (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  প্রতি (i=0 ; i < 8 * পরিমাণ (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, পূর্ণাঙ্ক);
  TEST (ffsl, long পূর্ণাঙ্ক);
  TEST (ffsll, long long পূর্ণাঙ্ক);

  প্রত্যাগম 0;
}

#অন্তর্ভাব <support/test-driver.c>

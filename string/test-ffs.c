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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <support/check.h>

void try (const var_na *name, long long ចំនួនគត់ param, ចំនួនគត់ value, ចំនួនគត់ expected)
{
  ប្រសិនបើ (value != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, value);
      support_record_failure ();
    }
  បើមិនដូច្នេះ
    printf ("%s(%#llx) as expected %d\n", name, param, value);
}

ចំនួនគត់
do_test (void)
{
  ចំនួនគត់ i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  សម្រាប់ (i=0 ; i < 8 * parimaa_na (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  សម្រាប់ (i=0 ; i < 8 * parimaa_na (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, ចំនួនគត់);
  TEST (ffsl, long ចំនួនគត់);
  TEST (ffsll, long long ចំនួនគត់);

  ត្រឡប់ 0;
}

#include <support/test-driver.c>

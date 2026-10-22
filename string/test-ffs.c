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

void try (const var_na *name, long long puur_naa_nka param, puur_naa_nka value, puur_naa_nka expected)
{
  ပေႃး (value != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, value);
      support_record_failure ();
    }
  ပေႃးဢမ်ႇ
    printf ("%s(%#llx) as expected %d\n", name, param, value);
}

puur_naa_nka
do_test (void)
{
  puur_naa_nka i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  for (i=0 ; i < 8 * parimaa_na (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  for (i=0 ; i < 8 * parimaa_na (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, puur_naa_nka);
  TEST (ffsl, long puur_naa_nka);
  TEST (ffsll, long long puur_naa_nka);

  ပွၵ်ႈ 0;
}

#include <support/test-driver.c>

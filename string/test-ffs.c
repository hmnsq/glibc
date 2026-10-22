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

#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <support/check.h>

શૂન્ય try (અચલ અક્ષર *name, long long પૂર્ણાંક param, પૂર્ણાંક કિંમત, પૂર્ણાંક expected)
{
  જો (કિંમત != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, કિંમત);
      support_record_failure ();
    }
  નહીંતર
    printf ("%s(%#llx) as expected %d\n", name, param, કિંમત);
}

પૂર્ણાંક
do_test (શૂન્ય)
{
  પૂર્ણાંક i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  માટે (i=0 ; i < 8 * કદ (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  માટે (i=0 ; i < 8 * કદ (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, પૂર્ણાંક);
  TEST (ffsl, long પૂર્ણાંક);
  TEST (ffsll, long long પૂર્ણાંક);

  પાછા 0;
}

#અન્તર્ભાવ <support/test-driver.c>

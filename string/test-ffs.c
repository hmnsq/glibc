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

#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <support/check.h>

வெறுமை try (மாறிலி எழுத்து *name, long long முழு param, முழு மதிப்பு, முழு expected)
{
  எனில் (மதிப்பு != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, மதிப்பு);
      support_record_failure ();
    }
  இல்லையெனில்
    printf ("%s(%#llx) as expected %d\n", name, param, மதிப்பு);
}

முழு
do_test (வெறுமை)
{
  முழு i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  க்கு (i=0 ; i < 8 * அளவு (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  க்கு (i=0 ; i < 8 * அளவு (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, முழு);
  TEST (ffsl, long முழு);
  TEST (ffsll, long long முழு);

  திரும்பு 0;
}

#அந்தர்பாவ <support/test-driver.c>

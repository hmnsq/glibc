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

#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <support/check.h>

ଶୂନ୍ୟ try (ଅଚଳ ଅକ୍ଷର *name, long long ପୂର୍ଣ୍ଣସଂଖ୍ୟା param, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା expected)
{
  ଯଦି (ମୂଲ୍ୟ != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, ମୂଲ୍ୟ);
      support_record_failure ();
    }
  ଅନ୍ୟଥା
    printf ("%s(%#llx) as expected %d\n", name, param, ମୂଲ୍ୟ);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
do_test (ଶୂନ୍ୟ)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  ପାଇଁ (i=0 ; i < 8 * ଆକାର (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  ପାଇଁ (i=0 ; i < 8 * ଆକାର (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
  TEST (ffsl, long ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
  TEST (ffsll, long long ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

  ଫେରନ୍ତୁ 0;
}

#ଅନ୍ତର୍ଭାଵ <support/test-driver.c>

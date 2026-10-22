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

#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <support/check.h>

ಶೂನ್ಯ try (ಧ್ರುವ ವರ್ಣ *name, long long ಪೂರ್ಣಾಙ್ಕ param, ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ, ಪೂರ್ಣಾಙ್ಕ expected)
{
  ಯದಿ (ಮೌಲ್ಯ != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, ಮೌಲ್ಯ);
      support_record_failure ();
    }
  ಅನ್ಯಥಾ
    printf ("%s(%#llx) as expected %d\n", name, param, ಮೌಲ್ಯ);
}

ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಙ್ಕ i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  ಪ್ರತಿ (i=0 ; i < 8 * ಪರಿಮಾಣ (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  ಪ್ರತಿ (i=0 ; i < 8 * ಪರಿಮಾಣ (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, ಪೂರ್ಣಾಙ್ಕ);
  TEST (ffsl, long ಪೂರ್ಣಾಙ್ಕ);
  TEST (ffsll, long long ಪೂರ್ಣಾಙ್ಕ);

  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>

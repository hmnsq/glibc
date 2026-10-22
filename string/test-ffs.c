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

ಶೂನ್ಯ try (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ param, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ, ಪೂರ್ಣಾಂಕ expected)
{
  ಆದರೆ (ಮೌಲ್ಯ != expected)
    {
      ಬರೆ ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, ಮೌಲ್ಯ);
      support_ದಾಖಲೆ_failure ();
    }
  ಇಲ್ಲದಿದ್ದರೆ
    ಬರೆ ("%s(%#llx) as expected %d\n", name, param, ಮೌಲ್ಯ);
}

ಪೂರ್ಣಾಂಕ
do_test (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಂಕ i;

#ವ್ಯಾಖ್ಯಾನಿಸು TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  ಗಾಗಿ (i=0 ; i < 8 * ಗಾತ್ರ (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  ಗಾಗಿ (i=0 ; i < 8 * ಗಾತ್ರ (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, ಪೂರ್ಣಾಂಕ);
  TEST (ffsl, ದೀರ್ಘ ಪೂರ್ಣಾಂಕ);
  TEST (ffsll, ದೀರ್ಘ ದೀರ್ಘ ಪೂರ್ಣಾಂಕ);

  ಹಿಂತಿರುಗಿ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>

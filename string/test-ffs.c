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

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <support/check.h>

शून्य try (ध्रुव वर्ण *name, long long पूर्णाङ्क param, पूर्णाङ्क मानम्, पूर्णाङ्क expected)
{
  जइ (मानम् != expected)
    {
      printf ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, मानम्);
      support_record_failure ();
    }
  अण्णहा
    printf ("%s(%#llx) as expected %d\n", name, param, मानम्);
}

पूर्णाङ्क
do_test (शून्य)
{
  पूर्णाङ्क i;

#define TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  प्रति (i=0 ; i < 8 * परिमाण (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  प्रति (i=0 ; i < 8 * परिमाण (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, पूर्णाङ्क);
  TEST (ffsl, long पूर्णाङ्क);
  TEST (ffsll, long long पूर्णाङ्क);

  प्रत्यागम 0;
}

#अन्तर्भाव <support/test-driver.c>

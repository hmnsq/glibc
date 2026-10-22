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

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <support/check.h>

శూన్య try (స్థిరరాశి అక్షరం *name, దీర్ఘ దీర్ఘ పూర్ణాంకం param, పూర్ణాంకం విలువ, పూర్ణాంకం expected)
{
  ఒకవేళ (విలువ != expected)
    {
      రాయి ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, విలువ);
      support_రికార్డు_failure ();
    }
  లేకపోతే
    రాయి ("%s(%#llx) as expected %d\n", name, param, విలువ);
}

పూర్ణాంకం
do_test (శూన్య)
{
  పూర్ణాంకం i;

#నిర్వచించు TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  కొరకు (i=0 ; i < 8 * పరిమాణం (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  కొరకు (i=0 ; i < 8 * పరిమాణం (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, పూర్ణాంకం);
  TEST (ffsl, దీర్ఘ పూర్ణాంకం);
  TEST (ffsll, దీర్ఘ దీర్ఘ పూర్ణాంకం);

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>

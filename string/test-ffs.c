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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>

ਖਾਲੀ try (ਅਚਲ ਅੱਖਰ *name, ਲੰਮਾ ਲੰਮਾ ਪੂਰਨ param, ਪੂਰਨ ਮੁੱਲ, ਪੂਰਨ expected)
{
  ਜੇ (ਮੁੱਲ != expected)
    {
      ਲਿਖੋ ("%s(%#llx) expected %d got %d\n",
	      name, param, expected, ਮੁੱਲ);
      support_ਰਿਕਾਰਡ_failure ();
    }
  ਨਹੀਂਤਾਂ
    ਲਿਖੋ ("%s(%#llx) as expected %d\n", name, param, ਮੁੱਲ);
}

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  ਪੂਰਨ i;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST(fct, type) \
  try (#fct, 0, fct ((type) 0), 0);					      \
  ਲਈ (i=0 ; i < 8 * ਆਕਾਰ (type); i++)				      \
    try (#fct, 1ll << i, fct (((type) 1) << i), i + 1);			      \
  ਲਈ (i=0 ; i < 8 * ਆਕਾਰ (type) ; i++)				      \
    try (#fct, (~((type) 0) >> i) << i, fct ((~((type) 0) >> i) << i), i + 1);\
  try (#fct, 0x80008000, fct ((type) 0x80008000), 16)

  TEST (ffs, ਪੂਰਨ);
  TEST (ffsl, ਲੰਮਾ ਪੂਰਨ);
  TEST (ffsll, ਲੰਮਾ ਲੰਮਾ ਪੂਰਨ);

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>

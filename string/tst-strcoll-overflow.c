/* Copyright (C) 2013-2026 Free Software Foundation, Inc.
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

#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.h>

/* Verify that strcoll does not crash for large strings for which it
   cannot cache weight lookup results.  The size is large enough to
   cause integer overflows on 32-bit as well as buffer overflows on
   64-bit.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮਾਪ_2 0x40000000ul

ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  TEST_VERIFY_EXIT (setlocale (LC_COLLATE, "en_GB.UTF-8") != ਨਿਰਾ);

  ਅੱਖਰ *p = ਸਮ੍ਰਿਤੀ_ਦਿਓ (ਮਾਪ_2);
  ਜੇ (p == ਨਿਰਾ)
    {
      puts ("info: could not allocate memory, cannot run test");
      ਵਾਪਸ EXIT_UNSUPPORTED;
    }

  memset (p, 'x', ਮਾਪ_2 - 1);
  p[ਮਾਪ_2 - 1] = 0;
  ਲਿਖੋ ("info: strcoll result: %d\n", strcoll (p, p));
  ਵਾਪਸ 0;
}

/* This test can rung for a long time, but it should complete within
   this time on reasonably current hardware.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TIMEOUT 300
#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>

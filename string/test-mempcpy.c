/* Test and measure mempcpy functions.
   Copyright (C) 1999-2026 Free Software Foundation, Inc.
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

#ವ್ಯಾಖ್ಯಾನಿಸು MEMCPY_ಫಲಿತಾಂಶ(dst, len) (dst) + (len)
#ವ್ಯಾಖ್ಯಾನಿಸು MIN_ಪುಟ_ಗಾತ್ರ 131072
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_MAIN
#ವ್ಯಾಖ್ಯಾನಿಸು TEST_NAME "mempcpy"
#ಅನ್ತರ್ಭಾವ "test-string.h"

IMPL (mempcpy, 1)

/* Naive implementation to verify results.  */
ಅಕ್ಷರ *
simple_mempcpy (ಅಕ್ಷರ *dst, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, size_t n)
{
  ಆಗ (n--)
    *dst++ = *src++;
  ಹಿಂತಿರುಗಿ dst;
}

#ಅನ್ತರ್ಭಾವ "test-memcpy.c"

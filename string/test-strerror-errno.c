/* BZ #24024 strerror and errno test.

   Copyright (C) 2019-2026 Free Software Foundation, Inc.
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

#ಅನ್ತರ್ಭಾವ <dlfcn.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ <support/check.h>
#ಅನ್ತರ್ಭಾವ <support/support.h>

/* malloc is allowed to change errno to a value different than 0, even when
   there is no actual error.  This happens for example when the memory
   allocation through sbrk fails.  Simulate this by interposing our own
   malloc implementation which sets errno to ENOMEM and calls the original
   malloc.  */
ಶೂನ್ಯ
*malloc (size_t size)
{
  ಸ್ಥಿರ ಶೂನ್ಯ *(*real_malloc) (size_t size);

  ಯದಿ (!real_malloc)
    real_malloc = dlsym (RTLD_NEXT, "malloc");

  errno = ENOMEM;

  ಪ್ರತ್ಯಾಗಮ (*real_malloc) (size);
}

/* strerror must not change the value of errno.  Unfortunately due to GCC bug
   #88576, this happens when -fmath-errno is used.  This simple test checks
   that it doesn't happen.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
do_test (ಶೂನ್ಯ)
{
  ವರ್ಣ *ಸಂದೇಶ;

  errno = 0;
  ಸಂದೇಶ = strerror (-3);
  (ಶೂನ್ಯ) ಸಂದೇಶ;
  TEST_COMPARE (errno, 0);

  locale_t l = xnewlocale (LC_ALL_MASK, "C", ರಿಕ್ತ);
  ಸಂದೇಶ = strerror_l (-3, l);
  (ಶೂನ್ಯ) ಸಂದೇಶ;
  TEST_COMPARE (errno, 0);

  ಪ್ರತ್ಯಾಗಮ 0;
}

#ಅನ್ತರ್ಭಾವ <support/test-driver.c>

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

#অন্তর্ভাব <dlfcn.h>
#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব <support/check.h>
#অন্তর্ভাব <support/support.h>

/* malloc is allowed to change errno to a value different than 0, even when
   there is no actual error.  This happens for example when the memory
   allocation through sbrk fails.  Simulate this by interposing our own
   malloc implementation which sets errno to ENOMEM and calls the original
   malloc.  */
শূন্য
*malloc (size_t আকার_2)
{
  স্থির শূন্য *(*real_malloc) (size_t আকার_2);

  যদি (!real_malloc)
    real_malloc = dlsym (RTLD_পরবর্তী, "malloc");

  errno = ENOMEM;

  ফেরত (*real_malloc) (আকার_2);
}

/* strerror must not change the value of errno.  Unfortunately due to GCC bug
   #88576, this happens when -fmath-errno is used.  This simple test checks
   that it doesn't happen.  */
স্থির পূর্ণসংখ্যা
do_test (শূন্য)
{
  অক্ষর *বার্তা;

  errno = 0;
  বার্তা = strerror (-3);
  (শূন্য) বার্তা;
  TEST_COMPARE (errno, 0);

  locale_t l = xnewlocale (LC_ALL_MASK, "C", ফাঁকা);
  বার্তা = strerror_l (-3, l);
  (শূন্য) বার্তা;
  TEST_COMPARE (errno, 0);

  ফেরত 0;
}

#অন্তর্ভাব <support/test-driver.c>

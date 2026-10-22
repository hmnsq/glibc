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

#అన్తర్భావ <dlfcn.h>
#అన్తర్భావ <errno.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ <support/check.h>
#అన్తర్భావ <support/support.h>

/* malloc is allowed to change errno to a value different than 0, even when
   there is no actual error.  This happens for example when the memory
   allocation through sbrk fails.  Simulate this by interposing our own
   malloc implementation which sets errno to ENOMEM and calls the original
   malloc.  */
శూన్య
*జ్ఞాపకం_ఇవ్వు (size_t కొలత)
{
  స్థిర శూన్య *(*real_malloc) (size_t కొలత);

  ఒకవేళ (!real_malloc)
    real_malloc = dlsym (RTLD_తదుపరి, "malloc");

  errno = ENOMEM;

  తిరిగి (*real_malloc) (కొలత);
}

/* strerror must not change the value of errno.  Unfortunately due to GCC bug
   #88576, this happens when -fmath-errno is used.  This simple test checks
   that it doesn't happen.  */
స్థిర పూర్ణాంకం
do_test (శూన్య)
{
  అక్షరం *సందేశం;

  errno = 0;
  సందేశం = strerror (-3);
  (శూన్య) సందేశం;
  TEST_COMPARE (errno, 0);

  locale_t l = xnewlocale (LC_ALL_MASK, "C", ఖాళీ);
  సందేశం = strerror_l (-3, l);
  (శూన్య) సందేశం;
  TEST_COMPARE (errno, 0);

  తిరిగి 0;
}

#అన్తర్భావ <support/test-driver.c>

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

#अन्तर्भाव <dlfcn.h>
#अन्तर्भाव <errno.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव <support/check.h>
#अन्तर्भाव <support/support.h>

/* malloc is allowed to change errno to a value different than 0, even when
   there is no actual error.  This happens for example when the memory
   allocation through sbrk fails.  Simulate this by interposing our own
   malloc implementation which sets errno to ENOMEM and calls the original
   malloc.  */
शून्य
*दो_स्मृति (माप_प्रकार size)
{
  स्थिर शून्य *(*real_malloc) (माप_प्रकार size);

  यदि (!real_malloc)
    real_malloc = dlsym (RTLD_NEXT, "malloc");

  त्रुटि_सं = ENOMEM;

  फर्काऊ (*real_malloc) (size);
}

/* strerror must not change the value of errno.  Unfortunately due to GCC bug
   #88576, this happens when -fmath-errno is used.  This simple test checks
   that it doesn't happen.  */
स्थिर पूर्णाङ्क
do_test (शून्य)
{
  वर्ण *सन्देश;

  त्रुटि_सं = 0;
  सन्देश = म_त्रुटि (-3);
  (शून्य) सन्देश;
  TEST_COMPARE (त्रुटि_सं, 0);

  locale_t l = xnewlocale (LC_ALL_MASK, "C", रिक्त);
  सन्देश = strerror_l (-3, l);
  (शून्य) सन्देश;
  TEST_COMPARE (त्रुटि_सं, 0);

  फर्काऊ 0;
}

#अन्तर्भाव <support/test-driver.c>

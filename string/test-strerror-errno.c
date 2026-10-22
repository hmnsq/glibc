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

#समावेश <dlfcn.h>
#समावेश <errno.h>
#समावेश <string.h>

#समावेश <support/check.h>
#समावेश <support/support.h>

/* malloc is allowed to change errno to a value different than 0, even when
   there is no actual error.  This happens for example when the memory
   allocation through sbrk fails.  Simulate this by interposing our own
   malloc implementation which sets errno to ENOMEM and calls the original
   malloc.  */
व्योम
*दो_स्मृति (माप_प्रकार आकार)
{
  अटल व्योम *(*real_malloc) (माप_प्रकार आकार);

  अगर (!real_malloc)
    real_malloc = dlsym (RTLD_अग्र, "malloc");

  त्रुटि_सं = ENOMEM;

  वापस (*real_malloc) (आकार);
}

/* strerror must not change the value of errno.  Unfortunately due to GCC bug
   #88576, this happens when -fmath-errno is used.  This simple test checks
   that it doesn't happen.  */
अटल पूर्णांक
do_test (व्योम)
{
  अक्षर *संदेश;

  त्रुटि_सं = 0;
  संदेश = म_त्रुटि (-3);
  (व्योम) संदेश;
  TEST_COMPARE (त्रुटि_सं, 0);

  locale_t l = xnewlocale (LC_ALL_MASK, "C", शून्य);
  संदेश = strerror_l (-3, l);
  (व्योम) संदेश;
  TEST_COMPARE (त्रुटि_सं, 0);

  वापस 0;
}

#समावेश <support/test-driver.c>

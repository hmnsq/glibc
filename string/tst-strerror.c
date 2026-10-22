/* Test for strerror, strerror_r, and strerror_l.

   Copyright (C) 2020-2026 Free Software Foundation, Inc.
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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <array_length.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <support/support.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <support/check.h>

ਸਥਿਰ ਪੂਰਨ
do_test (ਖਾਲੀ)
{
  unsetenv ("LANGUAGE");

  xsetlocale (LC_ALL, "C");

  TEST_COMPARE_STRING (strerror (EINVAL), "Invalid argument");
  TEST_COMPARE_STRING (strerror (-1),     "Unknown error -1");

  {
    ਅੱਖਰ ਬਫਰ[32];
    TEST_COMPARE_STRING (strerror_r (EINVAL, ਬਫਰ, 8),
			 "Invalid argument");
    TEST_COMPARE_STRING (strerror_r (-1, ਬਫਰ, 8),
			 "Unknown");
    TEST_COMPARE_STRING (strerror_r (-1, ਬਫਰ, 16),
			 "Unknown error -");
    TEST_COMPARE_STRING (strerror_r (-1, ਬਫਰ, 32),
			 "Unknown error -1");
  }

  locale_t l = xnewlocale (LC_ALL_MASK, "pt_BR.UTF-8", ਨਿਰਾ);

  TEST_COMPARE_STRING (strerror_l (EINVAL, l), "Argumento inv\303\241lido");
  TEST_COMPARE_STRING (strerror_l (-1, l),     "Erro desconhecido -1");

  xuselocale (l);

  TEST_COMPARE_STRING (strerror (EINVAL), "Argumento inv\303\241lido");
  TEST_COMPARE_STRING (strerror (-1),     "Erro desconhecido -1");

  {
    ਅੱਖਰ ਬਫਰ[32];
    TEST_COMPARE_STRING (strerror_r (EINVAL, ਬਫਰ, 8),
			 "Argumento inv\303\241lido");
    TEST_COMPARE_STRING (strerror_r (-1, ਬਫਰ, 8),
			 "Erro de");
    TEST_COMPARE_STRING (strerror_r (-1, ਬਫਰ, 16),
			 "Erro desconheci");
    TEST_COMPARE_STRING (strerror_r (-1, ਬਫਰ, 32),
			 "Erro desconhecido -1");
  }

  freelocale (l);

  ਵਾਪਸ 0;
}

#ਅਨ੍ਤਰ੍ਭਾਵ <support/test-driver.c>
